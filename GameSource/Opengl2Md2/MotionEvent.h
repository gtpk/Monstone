#pragma once
namespace MarxEngine
{
	enum MouseAction
	{
		ACTION_DOWN,
		ACTION_UP
	};

	class MotionEvent
	{

	public:
		int button;
		int state;
		int x;
		int y;
	};
}