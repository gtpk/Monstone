#pragma once
#include "IGameStage.h"
#include "ImageControl.h"
#include "Snumber.h"
#include "defAnimations.h"
#include "KardNameFactory.h"
#include "UIBase.h"
namespace MarxEngine
{
	class LoadingScreen : public IGameStage
	{
	public:

		long long dt_timesleep = 2000;

	public:
		LoadingScreen()
		{
			addEventHandler(dynamic_cast<IEventHandler<ClickEventArgs>*> (this));
		}

	public:


		void onDrawScreen()
		{
			OnDraw(false);
		}
	public:

		void XboxControllerKeyEvent(WORD Button, bool Updown);
		void onShow();

		void eventReceived(UIBase* sender, ClickEventArgs e);

		void onUpdate(long long dt);

		void onClose() {
		}

		bool isCloseed() {
			return true;

		}
	};

}