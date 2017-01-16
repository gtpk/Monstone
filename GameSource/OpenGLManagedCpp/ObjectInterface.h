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
	public ref class ObjectInterface : public INotifyPropertyChanged
	{
	protected:

		
		ObservableCollection<ObjectInterface^>^ _Children;
		void OnPropertyChanged(String^ info)
		{
			PropertyChanged(this, gcnew PropertyChangedEventArgs(info));
			_Children = gcnew ObservableCollection<ObjectInterface^>();
		}

		PROPERTYDEFINE(String^, TextureName)
		PROPERTYDEFINE(String^, AlphaTextureName)
		PROPERTYDEFINE(float, Scale)
		PROPERTYDEFINE(int, CurrentName)
		PROPERTYDEFINE(String^, ObjectName)
		PROPERTYDEFINE(float, Width)
		PROPERTYDEFINE(float, Height)
		PROPERTYDEFINE(String^, ModelName)
		PROPERTYDEFINE(Vector3D^, Rotation)
		PROPERTYDEFINE(Vector3D^, Trance)

		
	public:
		Md2Object* root;

		property ObservableCollection<ObjectInterface^>^ Children
		{
			ObservableCollection<ObjectInterface^>^ get()
			{
				return _Children;
			}
		}
		virtual event PropertyChangedEventHandler^ PropertyChanged;

		void setNewPiece(Md2Object* mother, Md2Object* obj)
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
				else
				{
					var->DeletePiece(model);
				}
			}
		}

		bool isUnable = true;
		void SetMarxObject(Md2Object* obj)
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
			CurrentName = obj->GetUniqNumber();
			//if(obj != m_obj)
			ObjectName = gcnew String(obj->GetName().c_str());

			if (obj->model() != NULL)
			{
				ModelName = gcnew String(obj->model()->getMd2name().c_str());

				TextureName = gcnew String(obj->model()->getTextureName().c_str());

				AlphaTextureName = gcnew String(obj->model()->getAlphaTextureName().c_str());

				Scale = obj->model()->getScale();

				Width = obj->model()->GetPieceWidth();

				Height = obj->model()->GetPieceHeight();
			}
			

			Rotation = gcnew Vector3D(obj->getRotate()[0],
				obj->getRotate()[1],
				obj->getRotate()[2]);

			Trance = gcnew Vector3D(obj->getTranslate()[0],
				obj->getTranslate()[1],
				obj->getTranslate()[2]);

		}

	};

}