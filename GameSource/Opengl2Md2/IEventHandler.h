#pragma once
#include "IUIBase.h"

template<class T>
class IEventHandler
{
public:
	virtual void eventReceived(IUIBase* sender, T e)=0;
private:

};