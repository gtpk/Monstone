#pragma once
#include "CXBOXController.h"
#include <stdio.h>


class XBoxControllerManager
{
public:
	static XBoxControllerManager* getinstance()
	{
		if (inst == NULL)
		{
			inst = new XBoxControllerManager();
		}
		return inst;
	}
	CXBOXController* getController(int Num);

	

private:
	static XBoxControllerManager* inst;

	XBoxControllerManager();
	~XBoxControllerManager();

	CXBOXController* player[4];
	
};