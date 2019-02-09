#pragma once

#include "Task.hpp"
#include <map>
#include <memory>
#include <cassert>
#include <Siv3D/String.hpp>

namespace aiUtil::task {
//singltonクラス
class TaskSystem {
private:
	TaskSystem() = default;
	~TaskSystem() = default;

	std::list<std::shared_ptr<Task>> taskList_;

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
	/// s3d::Stringをタグとしてタスク生成
	/// </summary>
	template<class TYPE, typename ... Args>
	static inline void create(Args && ... args) {
		getInstance().taskList_.emplace_back(std::make_shared<TYPE>(std::forward<Args>(args)...));
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
				
				switch ((*taskIt)->mode_)
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
		}
	private:
	};

	static inline void update() {
		for (auto task : getInstance().taskList_) {
			if (task->updateCondition()) {
				task->update();
			}
		}
	}

};
}