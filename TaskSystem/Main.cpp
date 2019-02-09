
# include <Siv3D.hpp> // OpenSiv3D v0.3.1
#include "aiUtil/task/TaskSystem.hpp"

class Task01 : public aiUtil::task::Task {
public:
	Task01(s3d::String msg) 
		: Task()
		, msg_(msg){}

	void update() override final {
		Logger << msg_;
	}

private:
	s3d::String msg_;
};

void Main()
{
	using namespace aiUtil::task;
	Graphics::SetBackground(ColorF(0.8, 0.9, 1.0));

	TaskSystem::create<Task01>(U"tag01", U"test message");

	while (System::Update())
	{
		TaskSystem::update();
		break;
	}

	TaskSystem::clear();
	Logger << U"END!!!!!!";

}
