#pragma once

// Exclude rarely used parts of the windows headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


#include "Helper.h"
#pragma comment(lib,"Opengl2Md2.lib")
#include "../Opengl2Md2/Md2Player.h"
//#pragma comment(lib, "opengl32.lib")


//#include "OpenGL.h"


// To use these, we must add some references...
//	o PresentationFramework (for HwndHost)
//		* PresentationCore
//		* WindowsBase
using namespace System;
using namespace System::Windows;
using namespace System::Windows::Interop;
using namespace System::Windows::Input;
using namespace System::Windows::Media;
using namespace System::Runtime::InteropServices;

/*
#define GLUT_LEFT_BUTTON		0
#define GLUT_MIDDLE_BUTTON		1
#define GLUT_RIGHT_BUTTON		2
*/
namespace WPFOpenGLLib 
{
	public ref class Piece 
	{
	public:
		Piece()
		{

		}


	private:


    protected: 
		
		public :
		void SetNewPiece()
		{
			Opengl2md2::getInstance().SetNewPiece();
		}
	};
}
