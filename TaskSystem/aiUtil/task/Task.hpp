#pragma once

#include <Siv3D.hpp>
#include "TaskCondition.hpp"
#include "TaskFunction.hpp"

namespace aiUtil::task {
/*
TODO: タスク間通信
*/
class Task {
public:

	virtual ~Task() = default;
	virtual void update()
	{
		if (recursionCnt_++) {
			func_();
			return;
		}
		update();
		recursionCnt_ = 0;
	}

	/// <summary>
	/// 実行するかどうかの判定
	/// </summary>
	/// <returns></returns>
	virtual bool updateCondition();
	virtual void destroy() final;

protected:
	TaskCondition eraseCond_;
	TaskFunction func_;

	Task(TaskCondition eraseCond)
		: eraseCond_{ std::move(eraseCond) }
		, func_{ this, &Task::update }
		, recursionCnt_{ 0 }
	{}
	Task(TaskFunction func)
		: eraseCond_{}
		, func_{ std::move(func) }
		, recursionCnt_{ 0 }
	{}
	Task(TaskFunction func, TaskCondition eraseCond)
		: eraseCond_{ std::move(eraseCond) }
		, func_{ std::move(func) }
		, recursionCnt_{ 0 }
	{}
	Task()
		: Task(TaskCondition{})
	{}
private:
	friend class TaskSystem;
	size_t recursionCnt_;
};

inline bool Task::updateCondition()
{
	// cond_は削除フラグ
	return !eraseCond_.updateCondition();
}

inline void Task::destroy()
{
	eraseCond_ = true;
}
}
