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
#include "../Opengl2Md2/Md2Player.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;
using namespace System::Windows::Input;
using namespace System::Windows::Media;
using namespace System::Windows::Forms; // We derive from UserControl this time, so this ref is necessary

using namespace System::Windows::Media::Media3D;
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
	public ref class SelectObjectInterface : public INotifyPropertyChanged
	{
	private: 
		static SelectObjectInterface^ instance;
		SelectObjectInterface()
		{
			instance = this;
		}

		

		void OnPropertyChanged(String^ info)
		{
			PropertyChanged(this, gcnew PropertyChangedEventArgs(info));
		}

		PROPERTYDEFINE(String^,TextureName)
		PROPERTYDEFINE(String^,AlphaTextureName)
		PROPERTYDEFINE(float,Scale)
		PROPERTYDEFINE(int,CurrentName)
		PROPERTYDEFINE(float,Width)
		PROPERTYDEFINE(float,Height)
		PROPERTYDEFINE(String^,ModelName)
		PROPERTYDEFINE(Vector3D^,Rotation)
		PROPERTYDEFINE(Vector3D^,Trance)
	

	public:

		virtual event PropertyChangedEventHandler^ PropertyChanged;


		static SelectObjectInterface^ GetInstance()
		{
			if(instance == nullptr)
				instance = gcnew SelectObjectInterface();
			return instance;
		}


	};
}