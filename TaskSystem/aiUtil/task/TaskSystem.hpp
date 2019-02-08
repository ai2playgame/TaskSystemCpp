#pragma once

#include "Task.hpp"
#include <list>
#include <memory>
#include <Siv3D/String.hpp>

namespace aiUtil::task {
//singlton�N���X
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
	/// s3d::String���^�O�Ƃ��ă^�X�N����
	/// </summary>
	template<class TYPE, typename ... Args>
	static inline void create(const s3d::String tag, Args && ... args) {
		getInstance().taskList_.emplace(tag, std::make_shared<TYPE>(args...));
		return;
	}

	/// <summary>
	/// ��čX�V
	/// </summary>
	static void update() {
		for (auto task : getInstance().taskList_){
			task.second->update();
		}
	}

	/// <summary>
	/// �^�O���g���ă^�X�N�擾
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
	/// �^�X�N���폜����
	/// </summary>
	static void remove(const s3d::String& tag) {
		getInstance().taskList_.erase(tag);
	}

	/// <summary>
	/// �S�Ẵ^�X�N���폜����
	/// </summary>
	static void clear() {
		getInstance().taskList_.clear();
	}

};
}