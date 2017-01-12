#pragma once
#include "IGameStage.h"
#include "ImageControl.h"
#include "KingControl.h"
#include "Snumber.h"
class LoadingScreen : public IGameStage
{
public:
	ImageControl* LoadingScreenImage;
	ImageControl* Goimage;
	Snumber* numbertest;
	int LoadingPersent;

	long long dt_timesleep = 2000;

	KingControl* King[10];
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
		
		
		LoadingScreenImage->OnDraw();
		Goimage->OnDraw();
		for (int i = 0; i < 10; i++)
		{
			King[i]->OnDraw();
		}
		numbertest->OnDraw();
	}
	//void onDrawScreen()
	//{
	//	// Paint ǥ��, �׸��� ��ü
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

		LoadingScreenImage = CreateImageControl("go_01", "go_01", 300, 300);
		Goimage = CreateImageControl("gapu_01", "gapu_01",0, 300);
		for (int i = 0; i < 10; i++)
		{
			King[i] = new KingControl();
			King[i]->x = 0+ (110*i);
			King[i]->y = 0;
		}
		numbertest = new Snumber();
		numbertest->x = 150;
		numbertest->y = 150;
		numbertest->setNumber(123456789);
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
		for (int i = 0; i < 10; i++)
		{
			King[i]->onUpdate(dt);
		}
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

