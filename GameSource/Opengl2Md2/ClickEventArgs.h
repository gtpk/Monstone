#pragma once
#include "MotionEvent.h"
#include "Point.h"
class ClickEventArgs
{

public:
	ClickEventArgs(MotionEvent e)
	{
		m_MotionEvent = e;
	}
	MotionEvent m_MotionEvent;
	Point m_Position;
};
