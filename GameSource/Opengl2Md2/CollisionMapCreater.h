#pragma once
#include "CommonDataType.h"
#include <vector>
class CollisionMapCreater
{
public:
	CollisionMapCreater();
	~CollisionMapCreater();


	void onDraw();
	void onDrawPoint();
	void onDrawLine();
	void SetVertext(COMMONDATATYPE::Vector3d dot);
	void SetVertext(float x,float y);
	static CollisionMapCreater* getinstance()
	{
		if (inst == NULL)
		{
			inst = new CollisionMapCreater();
		}
		return inst;
	}
private:
	std::vector<COMMONDATATYPE::Vector3d> dotlist;

	static CollisionMapCreater* inst;
	
};