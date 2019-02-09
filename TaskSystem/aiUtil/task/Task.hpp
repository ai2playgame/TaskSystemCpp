#pragma once

#include <Siv3D.hpp>

namespace aiUtil::task
{
/*
TODO: �^�X�N�ԒʐM
*/
class Task {
public:

	virtual ~Task() = default;
	virtual void update() = 0;
	virtual void draw() const = 0;
	virtual void destroy() final;

protected:
	enum class TaskDestroyMode {
		None,		//Task::Destroy�������ŌĂяo���ƍ폜�ł���
		Destroy		//�폜
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