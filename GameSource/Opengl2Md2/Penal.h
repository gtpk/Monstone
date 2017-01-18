#pragma once
#include "ImageControl.h"
#include <vector>
#include "Grid.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"

class Penal : public ImageControl
{
public:
	ImageControl* m_Container;

public :
	Penal()
	{
		ImageControl();
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
