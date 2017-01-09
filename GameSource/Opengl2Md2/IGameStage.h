#pragma once
#include "MotionEvent.h"
class IGameStage
{
public:
	virtual void onShow()=0;
	virtual void onDrawScreen() = 0;

	virtual void onTouchEvent(MotionEvent event) = 0;
	virtual void onUpdate(long dt) = 0;
	virtual void onClose() = 0;
	virtual bool isCloseed() = 0;
};
