#pragma once
#include "MotionEvent.h"
#include "RootUI.h"
namespace MarxEngine
{
	class IGameStage : public  RootUI
	{
	public:
		virtual void onShow() = 0;
		virtual void onDrawScreen() = 0;

		virtual void onUpdate(long long dt) = 0;
		virtual void onClose() = 0;
		virtual bool isCloseed() = 0;
		virtual void XboxControllerKeyEvent(WORD Button, bool Updown) = 0;
	};
}