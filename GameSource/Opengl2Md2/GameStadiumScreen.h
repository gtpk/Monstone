#pragma once
#include "Quad.h"
#include "Point.h"
#include "Opengl2md2.h"
#include "ExGameGraphicInfo.h"
#include "KardNameFactory.h"
#include "StageManager.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <cstdarg>
#include <cerrno>
#include <cmath>
#include <math.h>
using namespace std::chrono;

class GameStadiumScreen
{


public :
	GameStadiumScreen()
	{

	}

private :
	long ElpseTimer = 0;

public :
	void onDrawFrame()
	{
		
		milliseconds ms = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

		long dt = ms.count() - ElpseTimer;
		ElpseTimer = ms.count();
		StageManager::GetGameGraphic()->GetGameStage()->onUpdate(dt);
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2i(10, 400);
		GameStadiumScreen::glPrintf("rpriewajirojawiorjower");
		//glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
		glLoadIdentity();
		
		//m_quad.draw(gl);
		StageManager::GetGameGraphic()->GetGameStage()->onDrawScreen();
	}

	static int glPrintf(const char *format, ...)
	{
		char buffer[1024];
		std::va_list arg;
		int ret;

		// Format the text
		va_start(arg, format);
#ifndef _WIN32
		ret = std::vsnprintf(buffer, sizeof(buffer), format, arg);
#else
		ret = std::vsprintf(buffer, format, arg);
#endif

		va_end(arg);

		// Print it
		for (unsigned int i = 0; i < strlen(buffer); ++i)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, buffer[i]);

		return ret;
	}

	void onSurfaceChanged(int width, int height) 
	{
		// TODO Auto-generated method stub
		//glViewport(0, 0, width, height);
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		////GLU.gluPerspective(gl, 45.0f, (float) width / height, -20.0f, 30.0f);
		//gluOrtho2D( 0, 480, 800, 0);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//
		//Point GameSize;
		//GameSize.x = width;
		//GameSize.y = height;
		//ExGameGraphicInfo::GetGameGraphic()->SetGameSize(GameSize);

	}

	void onSurfaceCreated() 
	{
		
		// TODO Auto-generated method stub

		//m_quad.InitTexture(gl, ExGameInfo.GetGameInfo().GetContext());
		//glClearColor(0.87f, 0.87f, 0.87f, 0.0f);										// RGBA
		//glEnable(GL_TEXTURE_2D);									// 텍스쳐 활성
		//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);	// ??	
																//gl.glEnable(GL_LINE_SMOOTH);
																//gl.glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
		KardNameFactory::GetKardNameFactory()->OneTimeInit();

		ElpseTimer = system_clock::now().time_since_epoch().count();
	}

};
