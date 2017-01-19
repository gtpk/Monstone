#include "MainScreen.h"
using namespace MarxEngine;
namespace MarxEngine
{
	void MainScreen::onShow()
	{
		Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

		Background = ImageControl::CreateImageControl("imgame_back_06", "imgame_back_06", -10, -10);
		Background->SetWidth(GameSize.x + 20);
		Background->SetHeight(GameSize.y + 20);
		Background->SetAnimation(ImageControl::CreateAlphaAnimation(0, 255, 150, AnimationType::LinearEaseIn));
		Background->isNotClickable = false;
		addChild(Background);

		title = ImageControl::CreateImageControl("Monstonetitle", "Monstonetitle", 0, 0);
		title->isNotClickable = true;
		title->x = (GameSize.x - title->getWidth()) / 2;
		//title->y = (GameSize.y );
		//title->y = GameSize.y;
		title->SetAnimation(ImageControl::CreateTranslateYAnimation(GameSize.y, (GameSize.y - title->getHeight() + 10), 200, 150, AnimationType::CubicEaseOut));
		title->AnimationPlay();
		addChild(title);



		PressAny = ImageControl::CreateImageControl("pressany", "pressany", 0, 0);
		PressAny->x = (GameSize.x - PressAny->getWidth()) / 2;
		PressAny->isNotClickable = true;
		PressAny->transparent = 0;
		Spacial = ImageControl::CreateAlphaAnimation(50, 255, 150, 350, AnimationType::LinearEaseIn);
		Spacial->mRepeat = true;
		PressAny->SetAnimation(Spacial);
		PressAny->AnimationPlay();
		//title->y = (GameSize.y - title->getHeight());
		addChild(PressAny);

	}

	void MainScreen::eventReceived(UIBase* sender, ClickEventArgs e)
	{
		ImageControl* temp = dynamic_cast<ImageControl*>(sender);
		if (temp != NULL)
		{
			if (e.m_MotionEvent.state == GLUT_DOWN)
			{
				if (Spacial->isEnded())
				{

				}
				//printf("GLUT_DOWN");
			}
			else if (e.m_MotionEvent.state == GLUT_UP)
			{
				//printf("GLUT_UP");
			}
			else
			{
				//printf("%d",e.m_MotionEvent.state);
			}
			//printf(" %s\n", temp->Name.c_str());
		}

	}

}