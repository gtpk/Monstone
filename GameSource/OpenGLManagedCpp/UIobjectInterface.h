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
using System::ComponentModel::DescriptionAttribute;
using System::ComponentModel::CategoryAttribute;
using System::ComponentModel::DisplayNameAttribute;
using System::ComponentModel::ReadOnlyAttribute;
using System::ComponentModel::BrowsableAttribute;

// Exclude rarely used parts of the windows headers
//#define WIN32_LEAN_AND_MEAN
#define PROPERTYDEFINE(TYPE,NAME) property TYPE NAME\
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
}\
private:\
TYPE m_##NAME; \
public:\


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
	public:
		void MarshalString(String ^ s, string& os)
		{
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

	public:
		[Category("Common")]
		[DisplayName("Name")]
		property String^ Name
		{
			void set(String^ nName)
			{
				if(m_Name != nName)
				{
					m_Name = nName;
					OnPropertyChanged("Name");
				}
			}
			String^ get()
			{
				return m_Name;
			}
		}
	private:
		String^ m_Name; 


	public:
		[Category("Common")]
		[DisplayName("Marx Object Name")]
		property String^ ObjectName
		{
			void set(String^ nName)
			{
				if (m_ObjectName != nName)
				{
					m_ObjectName = nName;
					OnPropertyChanged("ObjectName");
				}
			}
			String^ get()
			{
				return m_ObjectName;
			}
		}
	private:
		String^ m_ObjectName;


		[Category("Brush")]
		[DisplayName("Texture Name"), ReadOnly(true)]
		PROPERTYDEFINE(String^, TextureName)

		[Category("Brush")]
		[DisplayName("transparent")]
		PROPERTYDEFINE(int, transparent)

		[Category("Layout")]
		[DisplayName("Scale X")]
		PROPERTYDEFINE(float, _ScaleX)

		[Category("Layout")]
		[DisplayName("Scale Y")]
		PROPERTYDEFINE(float, _ScaleY)

		[Category("Layout")]
		[DisplayName("Poisition X")]
		PROPERTYDEFINE(float, x)

		[Category("Layout")]
		[DisplayName("Poisition Y")]
		PROPERTYDEFINE(float, y)

		[Category("Layout")]
		[DisplayName("Z-Index")]
		PROPERTYDEFINE(float, zindex)

		[Category("Layout")]
		[DisplayName("Rotate")]
		PROPERTYDEFINE(float, rotate)

		[Category("Layout")]
		[DisplayName("Width")]
		PROPERTYDEFINE(float, Width)

		[Category("Layout")]
		[DisplayName("Height")]
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
				else
				{
					var->setNewPiece(mother,obj);
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
			//ObjectName = gcnew String(obj->GetName().c_str());
			ObjectName = gcnew String(obj->TextureName.c_str());
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