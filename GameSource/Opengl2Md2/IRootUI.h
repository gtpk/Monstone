#pragma once
#include "UIBase.h"
#include "ClickEventArgs.h"
namespace MarxEngine
{
	class IRootUI
	{
	public:
		virtual void OnCreate() = 0;
		virtual void OnDraw() = 0;
		virtual void OnTouch(UIBase* sender, ClickEventArgs e) = 0;
		virtual void OnShow() = 0;
		virtual void onClose() = 0;
		virtual void onUpdate(long long dt) = 0;
	};
}