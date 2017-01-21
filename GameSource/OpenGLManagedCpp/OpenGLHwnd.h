#pragma once

// Exclude rarely used parts of the windows headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


//#pragma comment(lib, "opengl32.lib")

//#pragma comment(lib, "Opengl2Md2.lib")




#include "Helper.h"

#pragma comment(lib,"Opengl2Md2.lib")
#include "../Opengl2Md2/Opengl2md2.h"
#include "../Opengl2Md2/ProjectLoader.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "SelectObjectInterface.h"
#include "UIobjectInterface.h"
#include "UIObjectTreeContator.h"
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
using namespace System::Windows::Forms;



/*
#define GLUT_LEFT_BUTTON		0
#define GLUT_MIDDLE_BUTTON		1
#define GLUT_RIGHT_BUTTON		2
*/
namespace WPFOpenGLLib 
{
	LRESULT WINAPI MyMsgProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
	{
		switch(_msg)
		{
			// Make sure the window gets focus when it has to!
			case WM_IME_SETCONTEXT:
				// LOWORD(wParam) = 0 stands for deactivation, so don't set
				// focus then (results in a rather, err... 'greedy' window...)
				if(LOWORD(_wParam) > 0) 
					SetFocus(_hWnd);

				return 0;
			case WM_SIZE:								// Resize The OpenGL Window
				{
					Opengl2md2::getInstance().reshape(LOWORD(_lParam),HIWORD(_lParam));

					//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
					return 0;								// Jump Back
				}
			case WM_KEYDOWN:							// Is A Key Being Held Down?
				{
					Opengl2md2::keyPress(_wParam,0,0); // If So, Mark It As TRUE
					Opengl2md2::specialKeyPress(_wParam,0,0);
					return 0;								// Jump Back
				}

			case WM_KEYUP:								// Has A Key Been Released?
				{
					Opengl2md2::keyUp(_wParam,0,0);					// If So, Mark It As FALSE
					Opengl2md2::specialKeyUp(_wParam,0,0);
					return 0;								// Jump Back
				}
			case WM_MOUSEMOVE:
				{
					Opengl2md2::mouseMotion(LOWORD(_lParam),HIWORD(_lParam));
					return 0;
				}
			case WM_LBUTTONDOWN:
				{
					Opengl2md2::mouseButton(GLUT_LEFT_BUTTON,GLUT_DOWN,LOWORD(_lParam),HIWORD(_lParam));
					SetFocus(_hWnd);
					return 0;
				}
			case WM_RBUTTONDOWN:
				{
					Opengl2md2::mouseButton(GLUT_RIGHT_BUTTON,GLUT_DOWN,LOWORD(_lParam),HIWORD(_lParam));
					SetFocus(_hWnd);
					return 0;
				}
			case WM_MBUTTONDOWN:
				{
					Opengl2md2::mouseButton(GLUT_MIDDLE_BUTTON,GLUT_DOWN,LOWORD(_lParam),HIWORD(_lParam));
					SetFocus(_hWnd);
					return 0;
				}
			case WM_LBUTTONUP:
				{
					Opengl2md2::mouseButton(GLUT_LEFT_BUTTON,GLUT_UP,LOWORD(_lParam),HIWORD(_lParam));
					return 0;
				}
			case WM_RBUTTONUP:
				{
					Opengl2md2::mouseButton(GLUT_RIGHT_BUTTON,GLUT_UP,LOWORD(_lParam),HIWORD(_lParam));
					return 0;
				}
			case WM_MBUTTONUP:
				{
					Opengl2md2::mouseButton(GLUT_MIDDLE_BUTTON,GLUT_UP,LOWORD(_lParam),HIWORD(_lParam));
					return 0;
				}
			case WM_MOUSEWHEEL:
				{
					//Opengl2md2::mouseButton(GLUT_MIDDLE_BUTTON,GLUT_UP,LOWORD(_lParam),HIWORD(_lParam));
					Opengl2md2::WhellScrolle(LOWORD(_wParam),HIWORD(_wParam));
					return 0;
				}
		    case WM_MOUSEACTIVATE:
				if( (HWND)_wParam != _hWnd) //hWndVP is hwnd of window I want to get focus
					return MA_NOACTIVATE;
				else
				{
					SetFocus(_hWnd);
					return MA_ACTIVATE;
				}
			case WM_PRINT:
				{
					
					//Opengl2md2::getInstance().idleVisible();
					//wglMakeCurrent(m_hDC, m_hRC);

					//Opengl2md2::getInstance().display();

					//SwapBuffers((GetDC(_hWnd));
					//Opengl2md2::getInstance().display();

					//SwapBuffers(GetDC(_hWnd)); // NOTE: This is no longer wglSwapBuffers
				}
			case WM_COMMAND:
				{
					Opengl2md2::menuSelect((HMENU)_lParam, _wParam);
					return 0;
				}
			default:
				return DefWindowProc( _hWnd, _msg, _wParam, _lParam );
		}
	}

	//
	// This class implements HwndHost
	//
	// We have to overwrite BuildWindowCore and DestroyWindowCore
	//
	// A very simple example which creates a Win32 ListBox can be found in the MSDN:
	// http://msdn2.microsoft.com/en-us/library/aa970061.aspx
	//
	public ref class OpenGLHwnd : public HwndHost
	{
	public:
		OpenGLHwnd() : m_hRC(NULL),
				m_hDC(NULL),
				m_hWnd(NULL),
				m_hInstance(NULL),
				m_sWindowName(NULL),
				m_sClassName(NULL),
				m_fRotationAngle(0.0f)
		{

		}


	private:
		HGLRC					m_hRC;
		HDC						m_hDC;
		HWND					m_hWnd;
		HINSTANCE				m_hInstance;
		LPCWSTR					m_sWindowName;
		LPCWSTR					m_sClassName;

		float					m_fRotationAngle;

		// DPI Scaling
		double					m_dScaleX;
		double					m_dScaleY;

		//Opengl2md2				*m_MineMonster;

    protected: 
		/*
		virtual IntPtr WndProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, bool% handled) override
		{
			switch( msg )
			{
				case WM_IME_SETCONTEXT:
					if(LOWORD(wParam.ToInt32()) > 0)
						SetFocus(m_hWnd);

					handled = true;
					return System::IntPtr::Zero;
				case WM_SIZE:								// Resize The OpenGL Window
					{
						//Opengl2md2::getInstance().reshape(LOWORD(lParam),HIWORD(lParam));

						//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
						return System::IntPtr::Zero;								// Jump Back
					}
			} 

			handled = false;
			return System::IntPtr::Zero;
		}*/
		


		virtual bool TranslateAccelerator(System::Windows::Interop::MSG% msg, ModifierKeys modifiers) override
		{
			if (msg.message == WM_KEYDOWN && msg.wParam == IntPtr(VK_TAB))
			{
				// Handle Shift+Tab
				if (GetKeyState(VK_SHIFT))
				{
					if (GetFocus() == m_hWnd)
					{
						// We're at the beginning, so send focus to the previous WPF element
						//return this->KeyboardInputSite->OnNoMoreTabStops(
						//	gcnew TraversalRequest(FocusNavigationDirection::Previous));
					}
					else
						return (SetFocus(m_hWnd) != NULL);
				}
				// Handle Shift without Tab
				else
				{
					if (GetFocus() == m_hWnd)
					{
						// We're at the end, so send focus to the next WPF element
						//return this->KeyboardInputSite->OnNoMoreTabStops(
						//	gcnew TraversalRequest(FocusNavigationDirection::Next));
					}
					else
						return (SetFocus(m_hWnd) != NULL);
				}
			}
		}
		
		virtual bool TabInto(TraversalRequest^ request) override
		{
			SetFocus(m_hWnd);
			return true;
		}
		//
		// Communicating with this method will be considerably more complicated in a real-
		// world application...
		//
		virtual void OnRender(System::Windows::Media::DrawingContext^ drawingContext) override
		{
			UNREF(drawingContext);
			if(m_hDC == NULL || m_hRC == NULL)
				return;

			Opengl2md2::getInstance().idleVisible();
			//wglMakeCurrent(m_hDC, m_hRC);

			Opengl2md2::getInstance().display();

			SwapBuffers(m_hDC); // NOTE: This is no longer wglSwapBuffers
			//ValidateRect(m_hWnd,NULL);
			
		}

        virtual void DestroyWindowCore(HandleRef hwnd) override
		{
			if(NULL != m_hRC)
			{
				wglDeleteContext(m_hRC);
				m_hRC = NULL;
			}

			if(NULL != m_hWnd && NULL != m_hDC)
			{
				ReleaseDC(m_hWnd, m_hDC);
				m_hDC = NULL;
			}

			if(NULL != m_hWnd && m_hWnd == (HWND)hwnd.Handle.ToPointer())
			{
				::DestroyWindow(m_hWnd);
				m_hWnd = NULL;
			}

			UnregisterClass(m_sClassName, m_hInstance);
        }

		bool RegisterWindowClass()
		{
			//
			// Create custom WNDCLASS
			//
			WNDCLASS wndClass;

			if(GetClassInfo(m_hInstance, m_sClassName, &wndClass))
			{
				// Class is already registered!
				return true;
			}

			wndClass.style				= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			
			// Not providing a WNDPROC here results in a crash on my system:
			wndClass.lpfnWndProc		= (WNDPROC)MyMsgProc; 
			wndClass.cbClsExtra			= 0;
			wndClass.cbWndExtra			= 0;
			wndClass.hInstance			= m_hInstance;
			wndClass.hIcon				= LoadIcon(NULL, IDI_WINLOGO);
			wndClass.hCursor			= LoadCursor(0, IDC_ARROW);
			wndClass.hbrBackground		= 0;
			wndClass.lpszMenuName		= 0; // No menu
			wndClass.lpszClassName		= m_sClassName;

			// ... and register it
			if (!RegisterClass(&wndClass))
			{
				Helper::ErrorExit(L"RegisterWindowClass");
				return false;
			}

			return true;
		}

		

		//
		// This is the key method to override
		//
		virtual HandleRef BuildWindowCore(HandleRef hwndParent) override 
		{
			// Get HINSTANCE
			m_hInstance		= (HINSTANCE) GetModuleHandle(NULL);
			m_sWindowName	= L"Marx Engine";
			m_sClassName	= L"OGLClassHwnd";

			if(RegisterWindowClass())
			{
				// some default size
				int iWidth = 1280;
				int iHeight = 700;


				DWORD dwStyle = WS_CHILD | WS_VISIBLE;

				// Get the parent (WPF) Hwnd. This is important: Windows won't let you create
				// the Hwnd otherwise.
				HWND parentHwnd = (HWND)hwndParent.Handle.ToPointer();

				m_hWnd = CreateWindowEx(0,
										m_sClassName,
										m_sWindowName,
										dwStyle,
										0,	// X Pos
										0,	// Y Pos
										iWidth,
										iHeight,
										parentHwnd, // Parent
										0,	// Menu
										m_hInstance,
										0  ); // Param

				if(!m_hWnd)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				m_hDC = GetDC(m_hWnd);
				if(!m_hDC)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				
				//
				// Create PixelFormatDescriptor and choose pixel format
				//
				uint PixelFormat;

				BYTE iAlphaBits = 0;
				BYTE iColorBits = 32;
				BYTE iDepthBits = 16;
				BYTE iAccumBits = 0;
				BYTE iStencilBits = 0;

				static PIXELFORMATDESCRIPTOR pfd = 
				{
					sizeof(PIXELFORMATDESCRIPTOR),	//size
					1,								//version
					PFD_DRAW_TO_WINDOW|				//flags
					PFD_SUPPORT_OPENGL|
					PFD_DOUBLEBUFFER,
					PFD_TYPE_RGBA,					//pixeltype
					iColorBits,
					0, 0, 0, 0, 0, 0,				//color bits ignored
					iAlphaBits,						
					0,								//alpha shift ignored
					iAccumBits,						//accum. buffer
					0, 0, 0, 0,						//accum bits ignored
					iDepthBits,						//depth buffer
					iStencilBits,					//stencil buffer
					0,								//aux buffer
					PFD_MAIN_PLANE,					//layer type
					0,								//reserved
					0, 0, 0							//masks ignored
				};
				
				PixelFormat = ChoosePixelFormat(m_hDC, &pfd);
				if(!PixelFormat)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				if(!SetPixelFormat(m_hDC, PixelFormat, &pfd))
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				m_hRC = wglCreateContext(m_hDC);
				if(!m_hRC)
				{
					Helper::ErrorExit(L"BuildWindowCore");
				}

				if(!wglMakeCurrent(m_hDC, m_hRC))
				{

					Helper::ErrorExit(L"BuildWindowCore");
				}

				//
				// Get DPI information and store scaling relative to 96 DPI.
				// See http://msdn2.microsoft.com/en-us/library/ms969894.aspx
				//
				m_dScaleX = GetDeviceCaps(m_hDC, LOGPIXELSX) / 96.0;
				m_dScaleY = GetDeviceCaps(m_hDC, LOGPIXELSY) / 96.0;

				//glEnable(GL_DEPTH_TEST);
				//glDisable(GL_TEXTURE_2D);

				SetParent(m_hWnd, (HWND) hwndParent.Handle.ToPointer());


				if(m_hDC && m_hWnd)
				{
					int argc = 2;
					char str1[] = {"WPFOpenGLApp.exe"};


					string LoaderPath  = ProjectLoader::getinstance()->GetProjectPath();

					bool isSelect ;
					
					string sModelname;
					String^ selected ;
					if(LoaderPath == "")	
					{
						FolderBrowserDialog^ dialog = gcnew FolderBrowserDialog();
						isSelect = (dialog->ShowDialog() == DialogResult::OK);
						selected = dialog->SelectedPath;
					
						MarshalString(selected,sModelname);
						ProjectLoader::getinstance()->ProjectPath = sModelname;
					}
					
					
					char strDefaltPath[] = {"E:\\Monstone\\GameResource\\hueteotl" };
					char* strDialogPath = (char*)Marshal::StringToHGlobalAnsi(selected).ToPointer();
					char* strLoaderPath = (char*)LoaderPath.c_str();
					
					char *strs[2];
					if(LoaderPath != "")	
					{
						strs[0] = str1;
						strs[1] = strLoaderPath;
					}
					else if(isSelect)
					{
						strs[0] = str1;
						strs[1] = strDialogPath;
					}
					else
					{
						strs[0] = str1;
						strs[1] = strDefaltPath;
					}

					char **argv = strs;
					

					Opengl2md2::getInstance().Openflmd2init(argc,argv,m_hDC, m_hRC, m_hWnd);
					
					//프로젝트 파일 저장
					ProjectLoader::getinstance()->SaveProjectFile();

					//하위 프로젝트에서 CLI 접근할수있게 인터페이스 연결
					VolkesIterfaceTool* instance = new VolkesIterfaceTool();
					MarxWorld::getInstance().Volkes = (EXTERN::VolkesIterface*)instance;

					instance->OneTimeInit();
				}


				SetFocus(m_hWnd);
				CompositionTarget::Rendering += gcnew EventHandler(this, &OpenGLHwnd::Drawing);
				//Load();
				return HandleRef(this, IntPtr(m_hWnd));
			}

			return HandleRef(nullptr, System::IntPtr::Zero);
		}

		private :
		void Drawing(Object^ sender, EventArgs^ e)
		{
			if(m_hDC == NULL || m_hRC == NULL)
				return;


			Opengl2md2::getInstance().idleVisible();
			wglMakeCurrent(m_hDC, m_hRC);

			Opengl2md2::getInstance().display();

			SwapBuffers(m_hDC); // NOTE: This is no longer wglSwapBuffers
			ValidateRect(m_hWnd,NULL);
		}

		void MarshalString ( String ^ s, string& os ) 
		{
			using namespace Runtime::InteropServices;
			const char* chars = 
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}

		void MarshalString ( String ^ s, std::wstring& os ) 
		{
			using namespace Runtime::InteropServices;
			const wchar_t* chars = 
				(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}


	public :
		void SetNewPiece(String^ sprite)
		{
			//Opengl2md2::getInstance().SetNewPiece();
			string ssprite;

			MarshalString(sprite, ssprite);

			if (Opengl2md2::getInstance().Close2d)
			{
				MarxWorld::getInstance().setNewPiece(ssprite);
			}
			else
			{
				
				if (LogicCommon::UIObjectTreeContator::GetInstance()->isUnable == true)
				{
					MarxWorld::getInstance().setNewImageControl(ssprite);
				}
				else
				{
					MarxWorld::getInstance().setNewImageControl(LogicCommon::UIObjectTreeContator::GetInstance()->root,ssprite);
				}
			}
			

		}

		void SetNewPiece(String^ ModelName, String ^ TextureName)
		{
			//Opengl2md2::getInstance().SetNewPiece();
			string sModelname;
			string sTextureName;

			MarshalString(ModelName,sModelname);
			MarshalString(TextureName,sTextureName);

			MarxWorld::getInstance().setNewPiece(sModelname,sTextureName);
			
		}

		void SetNewPiece(float Width, float Height, String ^ TextureName)
		{

			string sTextureName;

			MarshalString(TextureName,sTextureName);
			
			MarxWorld::getInstance().setNewPiece(Width,Height,sTextureName);
			
		}

		void SetNewPiece(float Width, float Height, String ^ TextureName,String ^ TextureAlpha)
		{

			string sTextureName;
			string sTextureAlpha;

			MarshalString(TextureName,sTextureName);
			MarshalString(TextureAlpha,sTextureAlpha);
			
			if (LogicCommon::SelectObjectInterface::GetInstance()->isUnable == true)
			{
				MarxWorld::getInstance().setNewPiece(Width, Height, sTextureName, sTextureAlpha);
			}
			else
			{
				MarxWorld::getInstance().setNewPiece(LogicCommon::SelectObjectInterface::GetInstance()->root,Width, Height, sTextureName, sTextureAlpha);
			}
			
			
		}


		void DrawingCall()
		{
			if(m_hDC == NULL || m_hRC == NULL)
				return;

			Opengl2md2::getInstance().idleVisible();
			//wglMakeCurrent(m_hDC, m_hRC);

			Opengl2md2::getInstance().display();

			//SwapBuffers(m_hDC); // NOTE: This is no longer wglSwapBuffers
			//ValidateRect(m_hWnd,NULL);
		}

		void Save()
		{
			Opengl2md2::getInstance().Save();
		}

		void Load()
		{
			bool isSelect;

			string sModelname;
			String^ selected1;
			
			OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog();
			openFileDialog1->Filter = "Stage Files|*.xml";
			openFileDialog1->Title = "Select a Cursor File";
			// Show the Dialog.
			// If the user clicked OK in the dialog and
			// a .CUR file was selected, open it.
			isSelect = (openFileDialog1->ShowDialog() == DialogResult::OK);
			selected1 = openFileDialog1->FileName;

			MarshalString(selected1, sModelname);
			Opengl2md2::getInstance().Load(sModelname);
		}
	};
}
