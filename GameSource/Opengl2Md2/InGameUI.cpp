#include "InGameUI.h"
#include "XBoxControllerManager.h"
#include "MarxWorld.h"
using namespace MarxEngine;
namespace MarxEngine
{
	void InGameUI::onShow()
	{
		MarxWorld::getInstance().Load("E:\\Monstone\\NewProject\\Stage1.xml");
	}

	void InGameUI::eventReceived(UIBase* sender, ClickEventArgs e)
	{

	}


	void InGameUI::XboxControllerKeyEvent(WORD Button, bool Updown)
	{
	}

	void InGameUI::onUpdate(long long dt)
	{
		if (KardNameFactory::GetKardNameFactory()->IsLoaded == false)
		{
			return;
		}

		dt_timesleep -= dt;
		if (dt_timesleep < 0)
		{

		}
	}
}