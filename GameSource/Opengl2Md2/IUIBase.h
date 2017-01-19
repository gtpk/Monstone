#pragma once
#include "Point.h"
#include "UIBase.h"
namespace MarxEngine
{
	class IUIBase
	{
	public:
		virtual void SetWidth(float width) = 0;
		virtual void SetHeight(float height) = 0;
		virtual float getWidth() = 0;
		virtual float getHeight() = 0;
		virtual void SetActualX(float _X) = 0;
		virtual float GetActualx() = 0;
		virtual void SetActualY(float _Y) = 0;
		virtual float GetActualy() = 0;
		virtual bool isPrang(MotionEvent event, int point) = 0;
		virtual void onTouchEvent(MotionEvent event) = 0;
		virtual Point getGridNum() = 0;
		virtual void setGridNum(Point num) = 0;
		virtual Point getGridSize() = 0;
		virtual void setGridSize(Point num) = 0;
		virtual UIVertical::Aligen_Vertical getAligenVertical() = 0;
		virtual void setAligenVertical(UIVertical::Aligen_Vertical value) = 0;
		virtual UIHorizen::Aligen_Horizen getAligenHorizen() = 0;
		virtual void setAligenHorizen(UIHorizen::Aligen_Horizen value) = 0;

	};
}