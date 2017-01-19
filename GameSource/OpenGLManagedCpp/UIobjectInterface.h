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
#include "../Common/VolkesInterface.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "../Opengl2Md2/MarxWorld.h"
#include "../Opengl2Md2/ImageControl.h"

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
	public ref class UIobjectInterface : public INotifyPropertyChanged
	{
	protected:


		ObservableCollection<UIobjectInterface^>^ _Children;
		void OnPropertyChanged(String^ info)
		{
			PropertyChanged(this, gcnew PropertyChangedEventArgs(info));
			_Children = gcnew ObservableCollection<UIobjectInterface^>();
		}

		PROPERTYDEFINE(String^, Name)
		PROPERTYDEFINE(String^, TextureName)
		PROPERTYDEFINE(int, transparent)
		PROPERTYDEFINE(float, _ScaleX)
		PROPERTYDEFINE(float, _ScaleY)
		PROPERTYDEFINE(float, x)
		PROPERTYDEFINE(float, y)
		PROPERTYDEFINE(float, zindex)
		PROPERTYDEFINE(float, rotate)
		PROPERTYDEFINE(float, Width)
		PROPERTYDEFINE(float, Height)


	public:
		ImageControl* root;

		property ObservableCollection<UIobjectInterface^>^ Children
		{
			ObservableCollection<UIobjectInterface^>^ get()
			{
				return _Children;
			}
		}
		virtual event PropertyChangedEventHandler^ PropertyChanged;


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

		bool isUnable = true;
		void SetMarxObject(ImageControl* obj)
		{

			root = obj;
			if (obj == NULL)
			{
				isUnable = true;
				return;
			}
			else
			{
				isUnable = false;
			}
			Name = gcnew String(obj->Name.c_str());
			TextureName = gcnew String(obj->TextureName.c_str());
			transparent = obj->transparent;
			_ScaleX = obj->ScaleX;
			_ScaleY = obj->ScaleY;
			x = obj->x;
			y = obj->y;
			zindex = obj->zindex;
			rotate = obj->m_rotate;
			Width = obj->m_Size.x;
			Height = obj->m_Size.y;

		}

	};

}