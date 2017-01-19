#pragma once
#include "Point.h"
#include "PointF.h"
#include "MotionEvent.h"
#include "ClickEventArgs.h"
#include "IContainer.h"
namespace MarxEngine
{
	namespace UIVertical
	{
		enum Aligen_Vertical
		{
			defalt,
			Right,
			Mid,
			Left,
			fiil,
		};
	};

	namespace UIHorizen
	{
		enum Aligen_Horizen
		{
			defalt,
			Top,
			Mid,
			Bottom,
			fiil,
		};

	}

	class UIBase : public IContainer
	{
	public:
		UIBase()
		{
			//m_gridNum(0, 0);
		}
		UIVertical::Aligen_Vertical m_Aligen_Vertical;
		UIHorizen::Aligen_Horizen m_Aligen_Horizen;
		Point m_gridNum;
		Point m_gridSize;

		PointF m_Size;

		float _Acturalx;
		float _Acturaly;

		bool isCaculated;

		float Mouse_x = 0;
		float Mouse_y = 0;

		float minimum_x = 0;
		float minimum_y = 0;

		float total_x = 0;
		float total_y = 0;

		bool visiable = true;
		bool isNotClickable = false;


		float getWidth() { return m_Size.x; }
		float getHeight() { return m_Size.y; }


		virtual void SetWidth(float width); //@Override

		virtual void SetHeight(float height); //@Override


		bool isPrang(MotionEvent e, int pointCount);


		void eventReceived(UIBase* sender, ClickEventArgs e) { } //@Override

		Point getGridNum() { return m_gridNum; } //@Override

		void setGridNum(Point num) { m_gridNum = num; } //@Override

		UIVertical::Aligen_Vertical getAligenVertical() { return m_Aligen_Vertical; } //@Override

		void setAligenVertical(UIVertical::Aligen_Vertical value) { m_Aligen_Vertical = value; } //@Override

		UIHorizen::Aligen_Horizen getAligenHorizen() { return m_Aligen_Horizen; } //@Override

		void setAligenHorizen(UIHorizen::Aligen_Horizen value) { m_Aligen_Horizen = value; } //@Override

		Point getGridSize() { return m_gridSize; } //@Override

		void setGridSize(Point num) { m_gridSize = num; } //@Override


		void SetActualX(float _X) {
			isCaculated = true;
			_Acturalx = _X;
		}

		//@Override
		void SetActualY(float _Y) {
			isCaculated = true;
			_Acturaly = _Y;
		}

		//@Override
		float GetActualx() {
			if (isCaculated)
				return _Acturalx;
			else
				return x;
		}

		//@Override
		float GetActualy() {
			if (isCaculated)
				return _Acturaly;
			else
				return y;

		}

	};

}