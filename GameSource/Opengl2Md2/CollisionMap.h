#pragma once
#include "CommonDataType.h"
#include <vector>
class CollisionMap
{
public:
	CollisionMap();
	~CollisionMap();


	void onDraw();
	void onDrawPoint();
	void onDrawLine();
	void SetVertext(COMMONDATATYPE::Vector3d dot);
	void SetVertext(float x, float y);

private:

	bool isFinish = false;
	std::vector<COMMONDATATYPE::Vector3d> dotlist;
	std::vector<int> polygonList;

};