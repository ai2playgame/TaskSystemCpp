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
	virtual void draw() const = 0;
	virtual void destroy() final;

protected:
	enum class TaskDestroyMode {
		None,		//Task::Destroyを自分で呼び出すと削除できる
		Destroy		//削除
	};
	TaskDestroyMode mode_;

	Task(const TaskDestroyMode mode);	
private:
	friend class TaskSystem;

};

inline void Task::destroy()
{
	mode_ = TaskDestroyMode::Destroy; 
}

Task::Task(const TaskDestroyMode mode)
	:mode_(mode){}

}