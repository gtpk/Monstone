#pragma once
#include "UIBase.h"

template<class T>
class IEventHandler
{
public:
	virtual void eventReceived(UIBase* sender, T e)=0;
private:

};