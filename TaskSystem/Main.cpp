
#include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include <random>
#include "aiUtil/task/TaskSystem.hpp"

class Task01 : public aiUtil::task::Task {
public:
	Task01(const Vec2& pos) 
		: Task(Task::TaskExecuteMode::None)
		, radius_(Random(30.f, 100.f))
		, pos_(pos)
	{}

	void update() override final {
		if (radius_ >= 1.0) {
			Circle(pos_, radius_).draw(Palette::Purple);
			radius_ -= 1.f;
		}
		else {
			destroy();
		}
		
	}

private:
	float radius_;
	Vec2 pos_;
};

void Main()
{
	using namespace aiUtil::task;
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	while (System::Update())
	{
		if (MouseL.down())
		{
			TaskSystem::create<Task01>(Cursor::PosF());
		}
		TaskSystem::update();
		TaskSystem::All::update();
	}

	TaskSystem::All::clear();
	Logger << U"END!!!!!!";

}
