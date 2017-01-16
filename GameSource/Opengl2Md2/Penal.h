#pragma once
#include "ImageControl.h"
#include <vector>
#include "IContainer.h"

#include "Grid.h"

class Penal : public ImageControl
{
private :
	ImageControl* m_Container;


public :
	Penal()
	{
		m_Container = (ImageControl*)(new Grid());
	}

public :
	void SetContainer(ImageControl* child)
	{
		m_Container = child;
	}

	void OnDraw(bool isSelect)
	{
		m_Container->OnDraw(isSelect);
	}

public :
	ImageControl* GetContainer()
	{
		return m_Container;
	}

public :
	void addChild(ImageControl* child)
	{
		m_Container->addChild(child);
	}

public :
	std::vector<ImageControl*>  getAllChild()
	{
		vector<ImageControl*> getAll_Child;
		getAll_Child.push_back(m_Container);
		return getAll_Child;
	}

public :
	void Remove(ImageControl* child) {
		m_Container->Remove(child);
	}

};
