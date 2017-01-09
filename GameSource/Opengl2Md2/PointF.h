#pragma once
class PointF
{
public:
	PointF() :x(0), y(0) {}
	PointF(float _x, float _y) { x = _x; y = _y; }
	float x;
	float y;
};