#pragma once
#include "KardNameFactory.h"
#include "IGameStage.h"
#include "MainScreen.h"
#define NULL 0
namespace StaticStage
{
	enum KADSTAGE
	{
		LOADING,
	};

}

class StageManager
{
	

private :
	StaticStage::KADSTAGE m_NowStage;


	// 로딩 화면
	MainScreen* m_LoadingScreen;


public :
	StageManager()
	{
		m_NowStage = StaticStage::KADSTAGE::LOADING;

		m_LoadingScreen = new MainScreen();


		SetNowStage(StaticStage::KADSTAGE::LOADING);

	}

private :
	static StageManager* m_StageManager;

public :
	static StageManager* GetGameGraphic()
	{
		if (m_StageManager == NULL)
			m_StageManager = new StageManager();
		
		return m_StageManager;
	}


private :
	IGameStage* TempStage;
private :
	StaticStage::KADSTAGE savedStage;
private :
	StaticStage::KADSTAGE before_savedStage;

public :
	IGameStage* GetGameStage();

public :
	IGameStage* GetGameBeforeStage();

public :
	IGameStage* GetGameStage(StaticStage::KADSTAGE stage);

public :
	void SetNowStage(StaticStage::KADSTAGE stage);

public :
	StaticStage::KADSTAGE GetNowStage()
	{
		return m_NowStage;
	}
};