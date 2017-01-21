#pragma once
#include "ImageControl.h"
#include <vector>
#include "Grid.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
namespace MarxEngine
{
	class Penal : public ImageControl
	{
	public:
		ImageControl* m_Container;

	public:
		Penal()
		{
			ImageControl();
			m_Container = (ImageControl*)(new Grid());
		}

	public:
		void SetContainer(ImageControl* child)
		{
			m_Container = child;
		}

		void OnDraw(bool isSelect)
		{
			m_Container->OnDraw(isSelect);
		}

	public:
		ImageControl* GetContainer()
		{
			return m_Container;
		}

	public:
		void addChild(ImageControl* child)
		{
			m_Container->addChild(child);
		}

	public:
		std::vector<ImageControl*>  getAllChild()
		{
			return m_Container->getAllChild();
		}

	public:
		void Remove(ImageControl* child) {
			m_Container->Remove(child);
		}

	public:
		ImageControl* GetImageControlByName(string Name);

	};
}