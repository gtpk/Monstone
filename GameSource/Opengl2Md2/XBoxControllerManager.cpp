#include "XBoxControllerManager.h"
XBoxControllerManager* XBoxControllerManager::inst = NULL;

XBoxControllerManager::XBoxControllerManager()
{
	for (int i = 0; i < 4; i++)
	{
		player[i] = new CXBOXController(i+1);
	}
}

XBoxControllerManager::~XBoxControllerManager()
{
	for (int i = 0; i < 4; i++)
	{
		delete (player[i]);
	}
}

CXBOXController* XBoxControllerManager::getController(int Num)
{
	if (Num < 0 && Num > 3)
		return NULL;
	else
		return player[Num];
}

