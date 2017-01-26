#include "EyeMouseMove.h"
#include "ViewCamera.h"
EyeMouseMove* EyeMouseMove::inst = NULL;
EyeMouseMove::EyeMouseMove()
{
}

EyeMouseMove::~EyeMouseMove()
{
}

void EyeMouseMove::SetMousePos(float x, float y,bool isClick)
{
	if (isActive == true)
	{
		if (isClick == true)
		{
			ViewCamera::getinstance()->eye.x = old_eye.x + (Last_mouse.x - x);
			ViewCamera::getinstance()->eye.y = old_eye.y + (y - Last_mouse.y);
		}
		else
		{
			
			old_eye = ViewCamera::getinstance()->eye;
			Last_mouse.x = x;
			Last_mouse.y = y;
		}
	}
	else
	{
		Last_mouse.x = x;
		Last_mouse.y = y;
	}
}

void EyeMouseMove::Enable()
{
	if (isActive == true)
		return;

	isActive = true;
	old_eye = ViewCamera::getinstance()->eye;
}

void EyeMouseMove::Disable()
{
	isActive = false;
}