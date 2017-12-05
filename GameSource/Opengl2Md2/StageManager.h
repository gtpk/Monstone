#pragma once
#include "KardNameFactory.h"
#include "IGameStage.h"
#include "MainScreen.h"
#include "InGameUI.h"
#include "LoadingScreen.h"
#define NULL 0
namespace StaticStage
{
	enum KADSTAGE
	{
		Title,
		LOADING,
		STORY,
	};

}
namespace MarxEngine
{
	class StageManager
	{


	private:
		StaticStage::KADSTAGE m_NowStage;


		// 로딩 화면
		LoadingScreen* m_LoadingScreen = NULL;
	public:
		StageManager()
		{
			m_NowStage = StaticStage::KADSTAGE::LOADING;

			m_LoadingScreen = new LoadingScreen();
		}

	private:
		static StageManager* m_StageManager;

	public:
		static StageManager* GetGameGraphic()
		{
			if (m_StageManager == NULL)
				m_StageManager = new StageManager();

			return m_StageManager;
		}


	private:
		IGameStage* TempStage;
	private:
		StaticStage::KADSTAGE savedStage;
	private:
		StaticStage::KADSTAGE before_savedStage;

	public:
		IGameStage* GetGameStage();

	public:
		IGameStage* GetGameBeforeStage();

	public:
		IGameStage* GetGameStage(StaticStage::KADSTAGE stage);

	public:
		void SetNowStage(StaticStage::KADSTAGE stage);

	public:
		StaticStage::KADSTAGE GetNowStage()
		{
			return m_NowStage;
		}
	};

}