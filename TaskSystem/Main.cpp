
# include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "aiUtil/task/TaskSystem.hpp"

class Task01 : public aiUtil::task::Task {
public:
	Task01() 
		: Task(Task::TaskExecuteMode::None)
		, pos_(Cursor::Pos())
		, radius_(Random(10.f, 40.f))
	{}

	void update() override final {
		if (radius_ <= 1.f) {
			destroy();
		}
		Circle(pos_, radius_).draw(Palette::Azure);
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
		if (MouseL.down()) {
			TaskSystem::create<Task01>();
		}
		TaskSystem::All::update();
		TaskSystem::TaskCall::update();
	}

	TaskSystem::All::clear();
	Logger << U"END!!!!!!";

}
