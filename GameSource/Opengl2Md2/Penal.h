#pragma once
#include "ImageControl.h"
#include <vector>
#include "IContainer.h"

#include "Grid.h"

class Penal : public ImageControl
{
private :
	IContainer* m_Container;


public :
	Penal()
	{
		m_Container = (IContainer*)(new Grid());
	}

public :
	void SetContainer(IContainer* child)
	{
		m_Container = child;
	}

public :
	IContainer* GetContainer()
	{
		return m_Container;
	}

public :
	void addChile(ImageControl* child)
	{
		m_Container->addChild(child);
	}

public :
	std::vector<IContainer*>  getAllChild()
	{
		vector<IContainer*> getAll_Child;
		getAll_Child.push_back(m_Container);
		return getAll_Child;
	}

public :
	void Remove(ImageControl* child) {
		m_Container->Remove(child);
	}

};
