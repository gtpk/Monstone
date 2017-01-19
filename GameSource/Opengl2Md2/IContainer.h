#pragma once
#include <vector>
#include "PointF.h"


namespace MarxEngine
{
	class ImageControl;

	class IContainer : public PointF
	{
	public:
		virtual void addChild(MarxEngine::ImageControl* child) = 0;

		virtual std::vector<MarxEngine::ImageControl*>  getAllChild() = 0;

		virtual void OnDraw(bool isSelect = false) = 0;

		virtual void Remove(MarxEngine::ImageControl* child) = 0;

		virtual bool AllAnimationFinished() = 0;
	};
}