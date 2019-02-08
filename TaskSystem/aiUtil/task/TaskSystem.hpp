#pragma once

#include "Task.hpp"
#include <list>
#include <memory>
#include <Siv3D/String.hpp>

namespace aiUtil::task {
//singltonクラス
class TaskSystem {
private:
	TaskSystem() = default;
	~TaskSystem() = default;

	using TaskPtr = std::shared_ptr<Task>;
	std::map<s3d::String, TaskPtr> taskList_;

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
	static inline void create(const s3d::String tag, Args && ... args) {
		getInstance().taskList_.emplace(tag, std::make_shared<TYPE>(args...));
		return;
	}

	/// <summary>
	/// 一斉更新
	/// </summary>
	static void update() {
		for (auto task : getInstance().taskList_){
			task.second->update();
		}
	}

	/// <summary>
	/// タグを使ってタスク取得
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	static TaskPtr getTask(const s3d::String& tag) {
		auto task = getInstance().taskList_.at[tag];
		if (task) {
			return task;
		}
		else {
			return nullptr;
		}
	}

	/// <summary>
	/// タスクを削除する
	/// </summary>
	static void remove(const s3d::String& tag) {
		getInstance().taskList_.erase(tag);
	}

	/// <summary>
	/// 全てのタスクを削除する
	/// </summary>
	static void clear() {
		getInstance().taskList_.clear();
	}

};
}