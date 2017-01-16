#pragma once
#include <vector>
#include "ImageControl.h"

class IContainer
{
public :
	virtual void addChild(ImageControl* child) = 0;

	virtual std::vector<ImageControl*>  getAllChild() =0;

	virtual void OnDraw(bool isSelect = false) =0;

	virtual void Remove(ImageControl* child)=0;

	virtual bool AllAnimationFinished() =0;
};
