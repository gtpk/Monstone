#pragma once
#include <stdio.h>
#include "CommonDataType.h"

class ViewCamera
{
public:
	static ViewCamera* getinstance()
	{
		if (inst == NULL)
		{
			inst = new ViewCamera();
		}
		return inst;
	}

	COMMONDATATYPE::Vector3d eye;

	float ViewScale = 1;
private:
	static ViewCamera* inst;

	ViewCamera();
	~ViewCamera();


};