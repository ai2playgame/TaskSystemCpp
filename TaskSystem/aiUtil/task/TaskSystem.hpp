#pragma once

#include "Task.hpp"
#include <list>

namespace aiUtil::task {
//singltonクラス
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
	/// 渡したタスクを削除し次のタスクのポインタを返す
	/// </summary>
	/// <param name="task"></param>
	/// <returns></returns>
	static Task* remove(Task* task);

	/// <summary>
	/// 全てのタスクを削除する
	/// </summary>
	static void clear();

};
}