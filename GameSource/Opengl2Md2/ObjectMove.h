#pragma once
#include <stdio.h>
#include "CommonDataType.h"
#include <vector>
#include "MarxObject.h"
#include "MarxWorld.h"

struct SelectObj
{
	float z1;
	float z2;
	int names;
	int index[50];
};

class ObjectMove
{
public:
	
	~ObjectMove();

	static ObjectMove* getinstance()
	{
		if (inst == NULL)
		{
			inst = new ObjectMove();
		}
		return inst;
	}
	std::vector<int> SelectObjectNum ;
	
	COMMONDATATYPE::mouse_input_t old_mouse;
	void OnDraw();
	
private:

	ObjectMove();
	std::vector<MarxObject*> SelectedObject;

	

	static ObjectMove* inst;
};

