#include "StageManager.h"

StageManager* StageManager::m_StageManager = NULL;


IGameStage* StageManager::GetGameStage()
{
	if (KardNameFactory::GetKardNameFactory()->IsReadForGame() == false)
		return m_LoadingScreen;

	if (savedStage != m_NowStage)
	{
		before_savedStage = savedStage;
		savedStage = m_NowStage;
		TempStage = GetGameStage(GetNowStage());
	}
	return TempStage;
}

IGameStage* StageManager::GetGameBeforeStage()
{
	if (KardNameFactory::GetKardNameFactory()->IsReadForGame() == false)
		return m_LoadingScreen;

	if (savedStage != m_NowStage)
	{
		before_savedStage = savedStage;
		savedStage = m_NowStage;
		TempStage = GetGameStage(GetNowStage());
	}
	return TempStage;
}

IGameStage* StageManager::GetGameStage(StaticStage::KADSTAGE stage)
{
	switch (stage) {
	case StaticStage::LOADING:
		return m_LoadingScreen;
	default:
		break;
	}
	return NULL;
}

void StageManager::SetNowStage(StaticStage::KADSTAGE stage)
{
	GetGameStage(m_NowStage)->onClose();
	m_NowStage = stage;

	GetGameStage(stage)->onShow();
}