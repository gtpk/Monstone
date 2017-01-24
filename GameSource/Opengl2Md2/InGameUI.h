#pragma once
#include "IGameStage.h"
#include "ImageControl.h"
#include "Snumber.h"
#include "defAnimations.h"
#include "KardNameFactory.h"
#include "UIBase.h"
#include "Momo.h"
namespace MarxEngine
{
	class InGameUI : public IGameStage
	{
	public:

		long long dt_timesleep = 200;
		
	public:
		InGameUI()
		{
			addEventHandler(dynamic_cast<IEventHandler<ClickEventArgs>*> (this));
		}
		Animation* CarmeraViewAniX = NULL;
		Animation* CarmeraViewAniY = NULL;
		Animation* CarmeraViewAniScale = NULL;
		Md2Object* king;
		Momo* king_obj;
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