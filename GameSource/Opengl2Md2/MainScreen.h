#pragma once
#include "IGameStage.h"
#include "ImageControl.h"
#include "Snumber.h"
#include "defAnimations.h"
#include "KardNameFactory.h"
#include "UIBase.h"
namespace MarxEngine
{
	class MainScreen : public IGameStage
	{
	public:

		int LoadingPersent;

		long long dt_timesleep = 2000;

		ImageControl* Background;
		ImageControl* title;
		ImageControl* PressAny;
		ImageControl* MainMenu;
		ImageControl* TitleWheel;
		ImageControl* MainMenuOption;
		ImageControl* MainMenuStart;
		ImageControl* MainMenuExit;

		Animation * Spacial;
		Animation * UPAni;
	public:
		MainScreen()
		{

			LoadingPersent = 0;


			addEventHandler(dynamic_cast<IEventHandler<ClickEventArgs>*> (this));

			//KardNameFactory.GetKardNameFactory().PlayOppeningSound();
			//KardNameFactory.GetKardNameFactory().StopBackgroundSound();
		}

	public:


		void onDrawScreen()
		{

			OnDraw(false);
			//King->OnDraw();
		}

		int selectValue = 0;


	public:

		void XboxControllerKeyEvent(WORD Button, bool Updown);
		void onShow();

		void eventReceived(UIBase* sender, ClickEventArgs e);

		void onUpdate(long long dt);

		void onClose() {
			// TODO Auto-generated method stub

		}

		bool isCloseed() {
			// TODO Auto-generated method stub
			return true;

		}
	};

}