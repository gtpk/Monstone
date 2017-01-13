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
#include "ObjectInterface.h"

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
	public ref class ObjectTreeContator : public ObjectInterface
	{
	private:
		static ObjectTreeContator^ instance;
		ObjectTreeContator()
		{
			instance = this;
			_Children = gcnew ObservableCollection<ObjectInterface^>();
		}

		ObservableCollection<ObjectInterface^>^ _Children;

		
	public :
		property ObservableCollection<ObjectInterface^>^ Children
		{
			ObservableCollection<ObjectInterface^>^ get()
			{
				return _Children;
			}
		}
		
		void DeletePiece(Md2Object* model)
		{
			for each (ObjectInterface^ var in Children)
			{
				if (var->root == model)
				{
					Children->Remove(var);
					return;
				}
			}
		}

		void setNewPiece(Md2Object* obj)
		{
			ObjectInterface^ gen = gcnew ObjectInterface();
			gen->SetMarxObject(obj);
			Children->Add(gen);
		}

		void setNewPiece(Md2Object* mother,Md2Object* obj)
		{
			ObjectInterface^ gen = gcnew ObjectInterface();
			gen->SetMarxObject(obj);

			for each (ObjectInterface^ var in Children)
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

		static ObjectTreeContator^ GetInstance()
		{
			if (instance == nullptr)
				instance = gcnew ObjectTreeContator();
			return instance;
		}
	};

}