#pragma once
#include "MotionEvent.h"
#include "RootUI.h"
class IGameStage : public  RootUI
{
public:
	virtual void onShow()=0;
	virtual void onDrawScreen() = 0;

	virtual void onUpdate(long long dt) = 0;
	virtual void onClose() = 0;
	virtual bool isCloseed() = 0;
};
