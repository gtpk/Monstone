//
// GLSAMPLE.CPP
//  by Blaine Hodge
//

// Includes

#include <windows.h>

#pragma comment(lib,"Opengl2Md2.lib")
#include "../../Opengl2Md2/Opengl2md2.h"
#include "../../Opengl2Md2/ProjectLoader.h"
#include "../../CLILogicCommon/VolkesInterfaceTool.h"
// Function Declarations


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

// WinMain

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{

	//콘솔 출력
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);//여기서 "CON"문자를 다른걸로 바꿔버리면 콘솔창에 출력이 안된다.
	//끝

	WNDCLASS wndClass;
	HWND hWnd = NULL;
	HDC hDC = NULL;
	HGLRC hRC = NULL;
	MSG msg;
	BOOL quit = FALSE;
	float theta = 0.0f;
	//HINSTANCE	m_hInstance = (HINSTANCE)GetModuleHandle(NULL);
	LPCWSTR		m_sWindowName = L"Marx Engine";
	LPCWSTR		m_sClassName = L"GLSample";

	// register window class
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = 0; // No menu
	wndClass.lpszClassName = m_sClassName;
	RegisterClass(&wndClass);


	

	DWORD dwStyle = WS_CHILD | WS_VISIBLE;
	// some default size
	int iWidth = 2;
	int iHeight = 2;

	// create main window
	hWnd = CreateWindow(
		m_sClassName, L"OpenGL Sample",
		WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE | WS_THICKFRAME | WS_MAXIMIZEBOX,
		0, 0, 1280, 720,
		NULL, NULL, hInstance, NULL);

	//
	// Create PixelFormatDescriptor and choose pixel format
	//
	

	// enable OpenGL for the window
	unsigned int PixelFormat;

	BYTE iAlphaBits = 0;
	BYTE iColorBits = 32;
	BYTE iDepthBits = 16;
	BYTE iAccumBits = 0;
	BYTE iStencilBits = 0;

	//static PIXELFORMATDESCRIPTOR pfd =
	//{
	//	sizeof(PIXELFORMATDESCRIPTOR),	//size
	//	1,								//version
	//	PFD_DRAW_TO_WINDOW |				//flags
	//	PFD_SUPPORT_OPENGL |
	//	PFD_DOUBLEBUFFER,
	//	PFD_TYPE_RGBA,					//pixeltype
	//	iColorBits,
	//	0, 0, 0, 0, 0, 0,				//color bits ignored
	//	iAlphaBits,
	//	0,								//alpha shift ignored
	//	iAccumBits,						//accum. buffer
	//	0, 0, 0, 0,						//accum bits ignored
	//	iDepthBits,						//depth buffer
	//	iStencilBits,					//stencil buffer
	//	0,								//aux buffer
	//	PFD_MAIN_PLANE,					//layer type
	//	0,								//reserved
	//	0, 0, 0							//masks ignored
	//};
	PIXELFORMATDESCRIPTOR pfd;
	int format;

	// get the device context (DC)
	hDC = GetDC(hWnd);

	// set the pixel format for the DC
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, format, &pfd);

	// create and enable the render context (RC)
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);
	//

	
	int argc = 2;
	char str1[] = { "WPFOpenGLApp.exe" };


	string LoaderPath = ProjectLoader::getinstance()->GetProjectPath();

	bool isSelect;
	TCHAR sPath[MAX_PATH] = { 0, };
	::GetCurrentDirectory(MAX_PATH, sPath);
	string sModelname;
	if (LoaderPath == "")
	{
		return 0 ;
	}

	char *strs[2];
	strs[0] = str1;
	strs[1] = (char*)LoaderPath.c_str();
	char **argv = strs;
	Opengl2md2::getInstance().Monstoneinit(argc, argv, hDC, hRC, hWnd);
	
	//MarxWorld::getInstance().Volkes = (EXTERN::VolkesIterface*)instance;
	glutInitDisplayMode(GLUT_RGB);
	// program main loop
	while (!quit)
	{

		// check for messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{

			// handle or dispatch messages
			if (msg.message == WM_QUIT)
			{
				quit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		else
		{
			Opengl2md2::getInstance().idleVisible();
			wglMakeCurrent(hDC, hRC);

			Opengl2md2::getInstance().display();

			SwapBuffers(hDC); // NOTE: This is no longer wglSwapBuffers
			ValidateRect(hWnd, NULL);

		}

	}

	// shutdown OpenGL
	DisableOpenGL(hWnd, hDC, hRC);

	// destroy the window explicitly
	DestroyWindow(hWnd);

	return msg.wParam;

}

// Window Procedure

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{

	switch (_msg)
	{
		// Make sure the window gets focus when it has to!
	case WM_IME_SETCONTEXT:
		// LOWORD(wParam) = 0 stands for deactivation, so don't set
		// focus then (results in a rather, err... 'greedy' window...)
		if (LOWORD(_wParam) > 0)
			SetFocus(_hWnd);

		return 0;
	case WM_SIZE:								// Resize The OpenGL Window
	{
		Opengl2md2::getInstance().reshape(LOWORD(_lParam), HIWORD(_lParam));

		//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		Opengl2md2::keyPress(_wParam, 0, 0); // If So, Mark It As TRUE
		Opengl2md2::specialKeyPress(_wParam, 0, 0);
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		Opengl2md2::keyUp(_wParam, 0, 0);					// If So, Mark It As FALSE
		Opengl2md2::specialKeyUp(_wParam, 0, 0);
		return 0;								// Jump Back
	}
	case WM_MOUSEMOVE:
	{
		Opengl2md2::mouseMotion(LOWORD(_lParam), HIWORD(_lParam));
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		Opengl2md2::mouseButton(GLUT_LEFT_BUTTON, GLUT_DOWN, LOWORD(_lParam), HIWORD(_lParam));
		SetFocus(_hWnd);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		Opengl2md2::mouseButton(GLUT_RIGHT_BUTTON, GLUT_DOWN, LOWORD(_lParam), HIWORD(_lParam));
		SetFocus(_hWnd);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		Opengl2md2::mouseButton(GLUT_MIDDLE_BUTTON, GLUT_DOWN, LOWORD(_lParam), HIWORD(_lParam));
		SetFocus(_hWnd);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		Opengl2md2::mouseButton(GLUT_LEFT_BUTTON, GLUT_UP, LOWORD(_lParam), HIWORD(_lParam));
		return 0;
	}
	case WM_RBUTTONUP:
	{
		Opengl2md2::mouseButton(GLUT_RIGHT_BUTTON, GLUT_UP, LOWORD(_lParam), HIWORD(_lParam));
		return 0;
	}
	case WM_MBUTTONUP:
	{
		Opengl2md2::mouseButton(GLUT_MIDDLE_BUTTON, GLUT_UP, LOWORD(_lParam), HIWORD(_lParam));
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		//Opengl2md2::mouseButton(GLUT_MIDDLE_BUTTON,GLUT_UP,LOWORD(_lParam),HIWORD(_lParam));
		Opengl2md2::WhellScrolle(LOWORD(_lParam), HIWORD(_lParam));
		return 0;
	}
	case WM_MOUSEACTIVATE:
		if ((HWND)_wParam != _hWnd) //hWndVP is hwnd of window I want to get focus
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
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	default:
		return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
	}
}

// Enable OpenGL

void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC  *hRC)
{
	

}

// Disable OpenGL

void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}


int main()
{
	return 0;
}