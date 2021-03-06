﻿
# include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "aiUtil/task/TaskSystem.hpp"

class Task01 : public aiUtil::task::Task {
public:
	Task01() 
		: Task(Task::TaskExecuteMode::None)
		, pos_(Cursor::Pos())
		, radius_(40.f)
	{}

	void update() override final {
		if (radius_ <= 1.f) {
			destroy();
			return;
		}
		Circle(pos_, radius_).draw(Palette::Purple);
		radius_ -= 1.f;
	}

private:
	Vec2 pos_;
	float radius_;
};

void Main()
{
	using namespace aiUtil::task;
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	while (System::Update())
	{
		try {
			if (MouseL.pressed()) {
				TaskSystem::create<Task01>();
			}
			if (MouseR.down()) {
				TaskSystem::createwithTag<Task01>(U"exeption_");
			}
			else if (MouseM.down()) {
				auto t = TaskSystem::getTask<Task>(U"missing Tag");
			}
		}
		catch(...){
			Logger << U"exception";
		}

		TaskSystem::All::update();
		TaskSystem::TaskCall::update();
	}

	TaskSystem::All::clear();
	Logger << U"END!!!!!!";

}
