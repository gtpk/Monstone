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
	}
}