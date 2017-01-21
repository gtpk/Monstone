#include "MainScreen.h"
#include "XBoxControllerManager.h"
#include "StageManager.h"

using namespace MarxEngine;
namespace MarxEngine
{
	void MainScreen::onShow()
	{
		Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

		Background = ImageControl::CreateImageControl("BackgroundTitle", "BackgroundTitle", -10, -10);
		Background->SetWidth(GameSize.x + 20);
		Background->SetHeight(GameSize.y + 20);
		Background->SetAnimation(ImageControl::CreateAlphaAnimation(0, 255, 150, AnimationType::LinearEaseIn));
		Background->isNotClickable = false;
		addChild(Background);

		title = ImageControl::CreateImageControl("Monstonetitle", "Monstonetitle", 0, 0);
		title->isNotClickable = true;
		title->x = (GameSize.x - title->getWidth()) / 2;
		title->y = (GameSize.y + 10);
		title->SetAnimation(ImageControl::CreateTranslateYAnimation(GameSize.y, (GameSize.y - title->getHeight() + 10), 200, 150, AnimationType::CubicEaseOut));
		title->AnimationPlay();
		addChild(title);
		UPAni = ImageControl::CreateTranslateYAnimation((GameSize.y - title->getHeight() + 10), 360, 100, AnimationType::CubicEaseOut);


		PressAny = ImageControl::CreateImageControl("pressany", "pressany", 0, 0);
		PressAny->x = (GameSize.x - PressAny->getWidth()) / 2;
		PressAny->isNotClickable = true;
		PressAny->transparent = 0;
		Spacial = ImageControl::CreateAlphaAnimation(50, 255, 150, 350, AnimationType::LinearEaseIn);
		Spacial->mRepeat = true;
		PressAny->SetAnimation(Spacial);
		PressAny->AnimationPlay();

		
		//title->y = (GameSize.y - title->getHeight());

		MainMenu = ImageControl::CreateImageControl("MainMenu", "MainMenu", 0, -49);
		//MainMenu->x = (GameSize.x - MainMenu->getWidth()) / 2;
		MainMenu->isNotClickable = true;
		MainMenu->visiable = false;
		addChild(MainMenu);
		{
			MainMenuStart = ImageControl::CreateImageControl(MainMenu,"MainMenuStart", "MainMenuStart", 6, 273);			MainMenu->addChild(MainMenuStart);
			MainMenuStart->transparent = 0;
			MainMenuStart->isNotClickable = false;
			MainMenuExit = ImageControl::CreateImageControl(MainMenu,"MainMenuExit","MainMenuExit", 19, 37);
			MainMenuExit->transparent = 0;
			MainMenuExit->isNotClickable = false;
			MainMenuOption = ImageControl::CreateImageControl(MainMenu, "MainMenuOption", "MainMenuOption", 0, 97);
			MainMenuOption->transparent = 0;
			MainMenuOption->isNotClickable = false;
		}




	}

	void MainScreen::eventReceived(UIBase* sender, ClickEventArgs e)
	{

		
		ImageControl* temp = dynamic_cast<ImageControl*>(sender);
		if (temp != NULL)
		{
			printf("%s\n", temp->Name.c_str());
			if (e.m_MotionEvent.state == GLUT_DOWN)
			{
				if (title->AnimationisEnded() && !MainMenu->visiable)
				{
					if (("BackgroundTitle" == temp->Name ))
					{
						Background->isNotClickable = true;
						MainMenu->visiable = true;
						PressAny->visiable = false;
						title->AnimationRemoveAll();
						title->SetAnimation(UPAni);
						title->AnimationPlay();
					}

					
				}
				if ("MainMenuOption" == temp->Name)
				{
					MainMenuOption->transparent = 255;
					MainMenuStart->transparent = 0;
					MainMenuExit->transparent = 0;
				}
				else if ("MainMenuStart" == temp->Name)
				{
					MainMenuOption->transparent = 0;
					MainMenuStart->transparent = 255;
					MainMenuExit->transparent = 0;
				}
				else if ("MainMenuExit" == temp->Name)
				{
					MainMenuOption->transparent = 0;
					MainMenuStart->transparent = 0;
					MainMenuExit->transparent = 255;
				}
			}
			else if (e.m_MotionEvent.state == GLUT_UP)
			{
			}
			else
			{
				//printf("%d",e.m_MotionEvent.state);
			}
		}

	}


	void MainScreen::XboxControllerKeyEvent(WORD Button, bool Updown)
	{
		if (title->AnimationisEnded() && !MainMenu->visiable)
		{
			if ((Button & XINPUT_GAMEPAD_START) && !Updown)
			{
				Background->isNotClickable = true;
				MainMenu->visiable = true;
				PressAny->visiable = false;
				title->AnimationRemoveAll();
				title->SetAnimation(UPAni);
				title->AnimationPlay();
			}
		}
		else if (MainMenu->visiable == true)
		{
			if ((Button & XINPUT_GAMEPAD_DPAD_UP  ) && !Updown)
			{
				if (selectValue > 1)
				{
					selectValue--;
				}
				//printf("XINPUT_GAMEPAD_DPAD_UP\n");

			}
			else if ((Button & XINPUT_GAMEPAD_DPAD_DOWN) && !Updown)
			{
				if (selectValue < 4)
				{
					selectValue++;
				}
				//printf("XINPUT_GAMEPAD_DPAD_DOWN\n");
			}

			if (selectValue == 1)
			{

				MainMenuStart->transparent = 255;
				MainMenuOption->transparent = 0;
				MainMenuExit->transparent = 0;
				if ((Button & XINPUT_GAMEPAD_A) && !Updown)
				{
					StageManager::GetGameGraphic()->SetNowStage(
						StaticStage::KADSTAGE::LOADING);
				}
			}
			else if (selectValue == 2)
			{
				MainMenuStart->transparent = 0;
				MainMenuOption->transparent = 255;
				MainMenuExit->transparent = 0;
			}
			else if (selectValue == 3)
			{
				MainMenuStart->transparent = 0;
				MainMenuOption->transparent = 0;
				MainMenuExit->transparent = 255;
			}
		}

	}

	void MainScreen::onUpdate(long long dt)
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