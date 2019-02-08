#pragma once

#include "Task.hpp"
#include <list>

namespace aiUtil::task {
//singlton�N���X
class TaskSystem {
private:
	TaskSystem() = default;
	~TaskSystem() = default;

public:
	TaskSystem(const TaskSystem&) = delete;
	TaskSystem& operator=(const TaskSystem&) = delete;
	TaskSystem(TaskSystem&&) = delete;
	TaskSystem& operator=(TaskSystem&&) = delete;

	static TaskSystem& get_instance() {
		static TaskSystem instance;
		return instance;
	}

	template<class TYPE>
	static inline TYPE* Create();

	/// <summary>
	/// �n�����^�X�N���폜�����̃^�X�N�̃|�C���^��Ԃ�
	/// </summary>
	/// <param name="task"></param>
	/// <returns></returns>
	static Task* remove(Task* task);

	/// <summary>
	/// �S�Ẵ^�X�N���폜����
	/// </summary>
	static void clear();

};
}