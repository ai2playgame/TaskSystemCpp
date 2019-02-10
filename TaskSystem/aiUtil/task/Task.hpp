#pragma once

#include <Siv3D.hpp>

namespace aiUtil::task
{
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
	virtual bool updateCondition() const;
	virtual void destroy() final;

protected:
	enum class TaskExecuteMode {
		None,			//Task::Destroyを自分で呼び出すと削除できる
		Destroy			//次のTask::All::update()で削除
	};
	TaskExecuteMode mode_;

	Task(const TaskExecuteMode mode);
private:
	friend class TaskSystem;

};

inline bool Task::updateCondition() const
{
	return true;
}

inline void Task::destroy()
{
	mode_ = TaskExecuteMode::Destroy;
}

Task::Task(const TaskExecuteMode mode)
	:mode_(mode){}

}