#include "ImageControl.h"
#include "Penal.h"
using namespace MarxEngine;

namespace MarxEngine
{
	ImageControl* Penal::GetImageControlByName(string Name)
	{
		vector<ImageControl*> cc = m_Container->getAllChild();
		vector<ImageControl*>::iterator itor = cc.begin();

		while (itor != cc.end())
		{
			ImageControl* node = *itor;
			if (node->Name == Name)
			{
				return node;
			}
			itor++;
		}
	}
}