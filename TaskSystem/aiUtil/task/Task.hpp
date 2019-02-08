#pragma once

#include <utility>

namespace aiUtil::task
{

/*
TODO: タスク間通信
*/
class Task {
public:	
	virtual ~Task() = default;
	virtual void update() = 0;
	virtual void draw() = 0;

private:
		
};


}