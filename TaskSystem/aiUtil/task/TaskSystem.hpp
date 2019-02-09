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

	static inline String createKey() noexcept {
		return ToString(getInstance().keyNumber_) + U"_";
	}

public:
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
	static inline void create(Args && ... args) {
		getInstance().taskList_
			.emplace(getInstance().createKey(),
				     std::make_shared<TYPE>(std::forward<Args>(args)...));
		getInstance().keyNumber_++;
		return;
	}

	template<class TYPE>
	static inline void create() {
		getInstance().taskList_
			.emplace(getInstance().createKey(),
				std::make_shared<TYPE>());
		getInstance().keyNumber_++;
		return;
	}


	/// <summary>
	/// s3d::Stringでタグを指定してタスク生成
	/// </summary>
	template<class TYPE, typename ... Args>
	static inline void createwithTag(const s3d::String tag, Args && ... args) {
		if (tag.back() == '_') {
			throw std::invalid_argument;
		}
		getInstance().taskList_.emplace(tag, std::make_shared<TYPE>(std::forward<Args>(args)...));
		return;
	}

	class All {
	public:
		/// <summary>
		/// 消去フラグが立っているタスクを削除
		/// </summary>
		static inline void update() {
			auto taskIt = getInstance().taskList_.begin();
			auto endIt = getInstance().taskList_.end();

			//末尾までループ
			while (taskIt != endIt){
				//次のタスクを指すイテレータを事前取得
				auto nextIt = std::next(taskIt);
				
				switch (taskIt->second->mode_)
				{
				case Task::TaskExecuteMode::None:
					break;
				
				//削除フラグが立っているので削除
				case Task::TaskExecuteMode::Destroy:
					getInstance().taskList_.erase(taskIt);
					break;

				//無効値
				default:
					assert(!"TaskDestroyMode is in bad state");
					break;
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
    static inline TaskPtr getTask(const s3d::String& tag) {
        if (getInstance().taskList_.count(tag) == 0)
            return nullptr;
        return getInstance().taskList_[tag];
    }

	/// <summary>
	/// タスクを削除する
	/// </summary>
	static void remove(const s3d::String& tag) {
		getInstance().taskList_.erase(tag);
	}

};
}