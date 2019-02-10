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
	
	/// <summary>
	/// ���s���邩�ǂ����̔���
	/// </summary>
	/// <returns></returns>
	virtual bool updateCondition() const;
	virtual void destroy() final;

protected:
	enum class TaskExecuteMode {
		None,			//Task::Destroy�������ŌĂяo���ƍ폜�ł���
		Destroy			//����Task::All::update()�ō폜
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