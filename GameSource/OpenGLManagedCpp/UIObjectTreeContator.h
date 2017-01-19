#pragma once
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma unmanaged
#include <strsafe.h>
#pragma managed

// Link lib
#pragma comment(lib, "strsafe.lib")

#define UNREF(x) x;

#include "stdio.h"
#include "../Opengl2Md2/Md2Object.h"
#include "../Opengl2Md2/Md2Model.h"
#include "../Opengl2Md2/MarxObject.h"
#include "../Common/VolkesInterface.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "../Opengl2Md2/MarxWorld.h"
#include "UIobjectInterface.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;
using namespace System::Windows::Input;
using namespace System::Windows::Media;
using namespace System::Windows::Forms; // We derive from UserControl this time, so this ref is necessary

using namespace System::Windows::Media::Media3D;
using namespace System::Collections::ObjectModel;
using namespace System::ComponentModel;


// Exclude rarely used parts of the windows headers
//#define WIN32_LEAN_AND_MEAN
#define PROPERTYDEFINE(TYPE,NAME) private:\
TYPE m_##NAME;\
public:\
property TYPE NAME\
{\
	void set(TYPE n##NAME)\
	{\
		if(m_##NAME != n##NAME)\
		{\
			m_##NAME = n##NAME;\
			OnPropertyChanged(#NAME);\
		}\
	}\
	TYPE get()\
	{\
		return m_##NAME;\
	}\
}


namespace LogicCommon
{
	public ref class UIObjectTreeContator : public UIobjectInterface
	{
	private:
		static UIObjectTreeContator^ instance;
		UIObjectTreeContator()
		{
			_Children = gcnew ObservableCollection<UIobjectInterface^>();
		}

		static ObservableCollection<UIobjectInterface^>^ _Children;


	public:
		property ObservableCollection<UIobjectInterface^>^ Children
		{
			ObservableCollection<UIobjectInterface^>^ get()
			{
				return UIObjectTreeContator::_Children;
			}
		}

		void DeletePiece(ImageControl* model)
		{
			for each (UIobjectInterface^ var in Children)
			{
				if (var->root == model)
				{
					Children->Remove(var);
					return;
				}
				else
				{
					var->DeletePiece(model);
				}
			}
		}

		void setNewPiece(ImageControl* obj)
		{
			UIobjectInterface^ gen = gcnew UIobjectInterface();
			gen->SetMarxObject(obj);
			Children->Add(gen);
		}

		void setNewPiece(ImageControl* mother, ImageControl* obj)
		{
			UIobjectInterface^ gen = gcnew UIobjectInterface();
			gen->SetMarxObject(obj);

			for each (UIobjectInterface^ var in Children)
			{
				if (var->root == mother)
				{
					var->Children->Add(gen);
					return;
				}
				else
				{
					var->setNewPiece(mother, obj);
				}
			}
		}

		static UIObjectTreeContator^ GetInstance()
		{
			if (instance == nullptr)
				instance = gcnew UIObjectTreeContator();
			return instance;
		}
	};

}