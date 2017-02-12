#include "InGameUI.h"
#include "XBoxControllerManager.h"
#include "MarxWorld.h"
#include "ViewCamera.h"
#include "MarxObject.h"
#include "ObjectNumberingMananger.h"
#include "LuaScriptAttached.h"
#include "ObjectManager.h"

using namespace MarxEngine;
namespace MarxEngine
{
	void InGameUI::onShow()
	{
		MarxWorld::getInstance().Load("E:\\Monstone\\NewProject\\Stage1.xml");

		///////////////////////// 테스트 플레이어
		king_obj = new Momo();

		
		king = new Md2Object(this);
		king->NotSave = true;

		king->setName(ObjectNumberingMananger::getInstance()->getNumber(king));
		king->m_obj = king_obj;
		king->setRotate(0, 90, 90);
		king->setScale(0.1);
		king->setTranslate(700,	400,0);
		LuaScriptAttached * attach = new LuaScriptAttached();
		king->OnAttech(attach);
		MarxWorld::getInstance().child.push_back(king);
		ObjectManager* m_ObjectManager = ObjectManager::GetInstance();
		m_ObjectManager->ReplaceMarxObject("KingPlayer", king);
		/////////////////////////
		Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();
		float CamFinalPosx = king->getTranslate()[0] - ((GameSize.x / 2.0f)*((float)GameSize.x / 1264.0f) );
		float CamFinalPosy = king->getTranslate()[1] - ((GameSize.y / 2.0f)*((float)GameSize.y / 682.0f));

		CarmeraViewAniX = ImageControl::CreateTranslateXAnimation(-500, CamFinalPosx, 300, AnimationType::LinearEaseIn);
		CarmeraViewAniY = ImageControl::CreateTranslateYAnimation(-400, CamFinalPosy, 300, AnimationType::LinearEaseIn);
		CarmeraViewAniScale = ImageControl::CreateScaleXAnimation(0.3, 0.85, 300, AnimationType::LinearEaseIn);
	}

	void InGameUI::eventReceived(UIBase* sender, ClickEventArgs e)
	{
		
	}


	void InGameUI::XboxControllerKeyEvent(WORD Button, bool Updown)
	{
		if (CarmeraViewAniX->isEnded())
		{
			if ((Button & XINPUT_GAMEPAD_DPAD_UP) && !Updown)
			{
				
			}
		}
	}

	void InGameUI::onUpdate(long long dt)
	{
		//currentX = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
		if (KardNameFactory::GetKardNameFactory()->IsLoaded == false)
		{
			return;
		}
		
		dt_timesleep -= dt;
		if (dt_timesleep < 0)
		{
			if(!CarmeraViewAniX->isEnded())
				ViewCamera::getinstance()->eye.x = CarmeraViewAniX->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - CarmeraViewAniX->mSaveStartTime);
			if (!CarmeraViewAniY->isEnded())
				ViewCamera::getinstance()->eye.y = CarmeraViewAniY->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - CarmeraViewAniX->mSaveStartTime);
			if (!CarmeraViewAniScale->isEnded())
				ViewCamera::getinstance()->ViewScale = CarmeraViewAniScale->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - CarmeraViewAniX->mSaveStartTime);
			if(CarmeraViewAniScale->isEnded())
			{
				

				king_obj->onUpdate(dt);
				CXBOXController* player = XBoxControllerManager::getinstance()->getController(0);

				bool isSelect = false;
				if ((player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT))
				{
					king->setTranslate_Lua(0.25*dt, 0, 0);
					king_obj->ScaleX = -1;
					ViewCamera::getinstance()->eye.x += (0.25*dt)*ViewCamera::getinstance()->ViewScale;
					isSelect = true;
				}
				if ((player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT))
				{
					king->setTranslate_Lua(-0.25*dt, 0, 0);
					king_obj->ScaleX = 1;
					ViewCamera::getinstance()->eye.x -= 0.25*dt*ViewCamera::getinstance()->ViewScale;
					isSelect = true;
				}
				if ((player->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN))
				{
					king->setTranslate_Lua(0, -0.25*dt, 0);
					ViewCamera::getinstance()->eye.y -= 0.25*dt*ViewCamera::getinstance()->ViewScale;
					isSelect = true;

				}
				if ((player->GetState().Gamepad.wButtons &  XINPUT_GAMEPAD_DPAD_UP))
				{
					king->setTranslate_Lua(0, 0.25*dt, 0);
					ViewCamera::getinstance()->eye.y += 0.25*dt*ViewCamera::getinstance()->ViewScale;
					isSelect = true;
				}
				if (isSelect == true)
				{
					king_obj->SetType(MomoStatus::Run);
				}
				else
				{
					king_obj->SetType(MomoStatus::Idle);
				}
				//Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();
				//float CamFinalPosx = king->getTranslate()[0] - ((GameSize.x / 2.0f)*ViewCamera::getinstance()->ViewScale);
				//float CamFinalPosy = king->getTranslate()[1] - ((GameSize.y / 2.0f)*ViewCamera::getinstance()->ViewScale);
				//
				//ViewCamera::getinstance()->eye.x = CamFinalPosx;
				//ViewCamera::getinstance()->eye.y = CamFinalPosy;
			}
			//캐릭터 따라가기 만들기!

		}
	}
}
