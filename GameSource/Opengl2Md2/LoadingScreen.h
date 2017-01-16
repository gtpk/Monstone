#pragma once
#include "IGameStage.h"
#include "ImageControl.h"
#include "KingControl.h"
#include "Snumber.h"
#include "Penal.h"

class LoadingScreen : public IGameStage , public Penal
{
public:

	int LoadingPersent;

	long long dt_timesleep = 2000;

	KingControl* King;
public :
	LoadingScreen()
	{
		KardNameFactory::GetKardNameFactory()->initBettleStage();

		LoadingPersent = 0;


		KardNameFactory::GetKardNameFactory()->OneTimeInit();
		//KardNameFactory.GetKardNameFactory().PlayOppeningSound();
		//KardNameFactory.GetKardNameFactory().StopBackgroundSound();
	}

public :
	ImageControl* CreateImageControl(string objectName,
		string ImageName, int x, int y) {
		ImageControl* _ImageControl = new ImageControl(objectName);
		_ImageControl->x = x;
		_ImageControl->y = y;
		_ImageControl->Name = objectName;
		return _ImageControl;
	}

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
	void onShow()
	{
		//KardNameFactory.GetKardNameFactory().StopBackgroundSound();

		King = new KingControl();
		King->x = 0;
		King->y = 0;
		addChild(King);
		//King->
		//LoadingScreenImage->SetAnimation(LoadingScreenImage->CreateAlphaAnimation(255, 0, dt_timesleep, 0, AnimationType::LinearEaseIn));
		//LoadingScreenImage->AnimationPlay();

		//KardNameFactory::GetKardNameFactory()->PlayRollingSound();
	}

	void onTouchEvent(MotionEvent event) 
	{
		// TODO Auto-generated method stub

	}


	void onUpdate(long long dt) 
	{
		// TODO Auto-generated method stub
		King->onUpdate(dt);

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

