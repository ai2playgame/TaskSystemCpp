#pragma once

#include <Siv3D.hpp>
#include "TaskCondition.hpp"

namespace aiUtil::task {
/*
TODO: タスク間通信
*/
class Task {
public:

	virtual ~Task() = default;
	virtual void update() = 0;

	/// <summary>
	/// 実行するかどうかの判定
	/// </summary>
	/// <returns></returns>
	virtual bool updateCondition();
	virtual void destroy() final;

protected:
	TaskCondition eraseCond_;

	Task(TaskCondition cond)
		: eraseCond_{ std::move(cond) }
	{}
	Task()
		: eraseCond_{}
	{}
private:
	friend class TaskSystem;

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
