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

		Animation * Spacial;
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
		//void onDrawScreen()
		//{
		//	// Paint 표시, 그리기 개체
		//	float Percent = KardNameFactory::GetKardNameFactory()->GetLoadingProgress();
		//	//cv.drawText("Now Loading.... " + (int)Percent + "%.." , 200, 435, paint);
		//
		//	if (Percent == 0)
		//	{
		//		if (KardNameFactory::GetKardNameFactory()->IsLoaded == false)
		//		{
		//			KardNameFactory::GetKardNameFactory()->initBettleStage();
		//			KardNameFactory::GetKardNameFactory()->OneTimeInit();
		//		}
		//	}
		//	if (Percent >= 100)
		//	{
		//		//StageManager::GetGameGraphic()->SetNowStage(StageManager.KADSTAGE.TIMEOUTGAME);
		//	}
		//}



	public:
		void onShow();

		void eventReceived(UIBase* sender, ClickEventArgs e);

		void onUpdate(long long dt)
		{

			//King->x = (GameSize.x - King->getWidth()) / 2;


			dt_timesleep -= dt;
			if (dt_timesleep < 0)
			{
				if (KardNameFactory::GetKardNameFactory()->IsLoaded == true)
				{
					//StageManager.GetGameGraphic().SetNowStage(StageManager.KADSTAGE.TIMEOUTGAME);
					return;
				}
			}
		}

		void onClose() {
			// TODO Auto-generated method stub

		}

		bool isCloseed() {
			// TODO Auto-generated method stub
			return true;

		}
	};

}