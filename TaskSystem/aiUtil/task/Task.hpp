#pragma once

#include <utility>

namespace aiUtil::task
{

/*
TODO: �^�X�N�ԒʐM
*/
class Task {
public:	
	virtual ~Task() = default;
	virtual void update() = 0;
	virtual void draw() = 0;

private:
		
};


}