#include "LoadingScreen.h"
#include "XBoxControllerManager.h"
#include "MarxWorld.h"
#include "StageManager.h"

using namespace MarxEngine;
namespace MarxEngine
{
	void LoadingScreen::onShow()
	{
		Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

		ImageControl* Background = ImageControl::CreateImageControl("imgame_back_06", "imgame_back_06", -10, -10);
		Background->SetWidth(GameSize.x + 20);
		Background->SetHeight(GameSize.y + 20);
		Background->SetAnimation(ImageControl::CreateAlphaAnimation(0, 255, 150, AnimationType::LinearEaseIn));
		Background->isNotClickable = false;
		addChild(Background);

		ImageControl*title = ImageControl::CreateImageControl("TitleWheel", "TitleWheel", 0, 0);
		title->isNotClickable = true;
		title->x = (1280 - title->getWidth()) / 2;
		title->y = (700 - title->getHeight()) / 2;
		Animation* Spacial = ImageControl::CreateRotationAnimation(0, 360, 300, AnimationType::LinearEaseIn);
		Spacial->mRepeat = true;
		title->SetAnimation(Spacial);
		title->AnimationPlay();
		addChild(title);
	}

	void LoadingScreen::eventReceived(UIBase* sender, ClickEventArgs e)
	{

	}


	void LoadingScreen::XboxControllerKeyEvent(WORD Button, bool Updown)
	{
	}

	void LoadingScreen::onUpdate(long long dt)
	{
		if (KardNameFactory::GetKardNameFactory()->IsLoaded == false)
		{
			return;
		}

		dt_timesleep -= dt;
		if (dt_timesleep < 0)
		{
			StageManager::GetGameGraphic()->SetNowStage(
				StaticStage::KADSTAGE::STORY);
		}
	}
}