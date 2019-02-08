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
	
private:
	
};


}