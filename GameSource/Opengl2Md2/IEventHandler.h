#pragma once
#include "UIBase.h"
using namespace MarxEngine;
namespace MarxEngine
{
	template<class T>
	class IEventHandler
	{
	public:
		virtual void eventReceived(UIBase* sender, T e) = 0;
	private:

	};
}