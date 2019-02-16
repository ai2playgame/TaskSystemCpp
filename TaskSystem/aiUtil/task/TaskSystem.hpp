#pragma once

#include "Task.hpp"
#include <map>
#include <memory>
#include <cassert>
#include <regex>
#include <Siv3D/String.hpp>

namespace aiUtil::task {
//singltonクラス
class TaskSystem {
private:
	TaskSystem() = default;
	~TaskSystem() = default;

	using TaskPtr = std::shared_ptr<Task>;
	std::unordered_map<s3d::String, TaskPtr> taskList_;
	
	size_t keyNumber_ = 0;

	/// <summary>
	/// ユーザーがキーを指定しないときにキーを生成する
	/// </summary>
	/// <returns></returns>
	static inline String createKey() noexcept {
		return ToString(getInstance().keyNumber_++) + U"_";
	}

public:
	//Singltonなのでdelete
	TaskSystem(const TaskSystem&) = delete;
	TaskSystem& operator=(const TaskSystem&) = delete;
	TaskSystem(TaskSystem&&) = delete;
	TaskSystem& operator=(TaskSystem&&) = delete;

	static TaskSystem& getInstance() {
		static TaskSystem instance;
		return instance;
	}

	/// <summary>
	/// タスク生成
	/// </summary>
	template<class TYPE, typename ... Args>
	static inline std::weak_ptr<TYPE> create(Args && ... args) {
		auto key = getInstance().createKey();
		getInstance().taskList_
			.emplace(key,
				     std::make_shared<TYPE>(std::forward<Args>(args)...));
		auto tmp = getInstance().getTask<TYPE>(key);
		return tmp;
	}

	/// <summary>
	/// s3d::Stringでkeyを指定してタスク生成
	/// </summary>
	template<class TYPE, typename ... Args>
	static inline std::weak_ptr<TYPE> createwithTag(const s3d::String& tag, Args && ... args) {
		if (tag.back() == '_') {
			throw std::invalid_argument("Task's tag is missing");
		}
		getInstance().taskList_.emplace(tag, std::make_shared<TYPE>(std::forward<Args>(args)...));
		auto tmp = getInstance().getTask<TYPE>(tag);
		return tmp;
	}

	class All {
	public:
		/// <summary>
		/// 消去フラグが立っているタスクを削除
		/// </summary>
		static inline void update() {

			//タスクリストの先頭と終端のイテレータを見る
			auto taskIt = getInstance().taskList_.begin();
			auto endIt = getInstance().taskList_.end();

			//もしタスクが空ならkeyNumber_を初期化
			if (taskIt == endIt) {
				getInstance().keyNumber_ = 0;
			}

			//末尾までループ
			while (taskIt != endIt){
				//次のタスクを指すイテレータを事前取得
				auto nextIt = std::next(taskIt);

                if (*(taskIt->second->eraseCond_)) {
					getInstance().taskList_.erase(taskIt);
                }
				taskIt = nextIt;
			}
		}

		/// <summary>
		/// 全てのタスクを削除する
		/// </summary>
		static inline void clear() noexcept {
			getInstance().taskList_.clear();
			getInstance().keyNumber_ = 0;
		}
	private:
	};

	class TaskCall {
	public:
		/// <summary>
		/// タスクのupdate()関数を呼び出す
		/// </summary>
		static inline void update() {
			for (auto task : getInstance().taskList_) {
				if (task.second->updateCondition()) {
					task.second->update();
				}
			}
		}
	private:
	};

	/// <summary>
	/// タグを使ってタスク取得
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
/*   
	static inline TaskPtr getTask(const s3d::String& tag) {
        if (getInstance().taskList_.count(tag) == 0)
            return nullptr;
        return getInstance().taskList_[tag];
    }
*/
	
	template<typename T>
	[[nodiscard]] static inline std::weak_ptr<T> getTask(const s3d::String& tag) {

		auto sp = std::dynamic_pointer_cast<T>(getInstance().taskList_.at(tag));
		return static_cast<std::weak_ptr<T>>(sp);
	}

	/// <summary>
	/// タスクを削除する
	/// </summary>
	static void remove(const s3d::String& tag) {
		getInstance().taskList_.erase(tag);
	}

};
}