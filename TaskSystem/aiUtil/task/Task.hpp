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
	
private:
	
};


}