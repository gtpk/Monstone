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
#include "SelectableObject.h"
#include "Quad.h"

using namespace std::chrono;
using namespace MarxEngine;
namespace MarxEngine
{
	class GameStadiumScreen : public SelectableObject
	{

		test::Quad* m_quad;
	public:
		GameStadiumScreen()
		{
			m_quad = new test::Quad();
		}

	private:
		long long ElpseTimer = 0;
		COMMONDATATYPE::Vector3d _p;
		COMMONDATATYPE::Vector3d GetNowPostion() { return _p; }
		void SetNowPostion(COMMONDATATYPE::Vector3d pos) {}
	public:
		void onDrawFrame()
		{
			glPushMatrix();

			//glOrtho(0, 480, 0, 800, -1.0f, 1.0f);

			milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

			long long dt = ms.count() - ElpseTimer;
			if (dt < 0)
				dt = 0;
			ElpseTimer = ms.count();
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


			StageManager::GetGameGraphic()->GetGameStage()->onUpdate(dt);

			glRasterPos2i(0, 0);
			//glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
			glLoadIdentity();
			Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

			glScaled((float)(GameSize.x / 1264.0f), (float)(GameSize.y / 682.0f), 1);
			//m_quad->draw();
			StageManager::GetGameGraphic()->GetGameStage()->onDrawScreen();
			glPopMatrix();
		}

		int _SelectID = - 1;


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

			//TODO Auto-generated method stub
			glViewport(0, 0, width, height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//GLU.gluPerspective(gl, 45.0f, (float) width / height, -20.0f, 30.0f);
			//gluOrtho2D( 0, 480, 800, 0);
			glOrtho(0,
				width,
				0,
				height,
				-1, 10000.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			Point GameSize;
			GameSize.x = width;
			GameSize.y = height;
			ExGameGraphicInfo::GetGameGraphic()->SetGameSize(GameSize);

		}

		void onSurfaceCreated()
		{

			// TODO Auto-generated method stub

			//m_quad.InitTexture(gl, ExGameInfo.GetGameInfo().GetContext());
			//glClearColor(0.87f, 0.87f, 0.87f, 0.0f);										// RGBA
			glEnable(GL_TEXTURE_2D);									// 텍스쳐 활성
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);	// ??	

																	//gl.glEnable(GL_LINE_SMOOTH);
																	//gl.glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); 
			KardNameFactory::GetKardNameFactory()->OneTimeInit();

			ElpseTimer = system_clock::now().time_since_epoch().count() / 100000;
		}
		bool m_isPressd = false;

		bool onTouchEvent(MotionEvent _event)
		{

			bool isPressd = false;
			switch (_event.state) {
			case GLUT_DOWN:
				isPressd = true;
				break;
			case GLUT_UP:
				isPressd = false;
				break;
			}
			if (isPressd == m_isPressd)
			{
				return true;
			}
			else
			{
				m_isPressd = isPressd;
				StageManager::GetGameGraphic()->GetGameStage()->onTouchEvent(_event);
			}
			return true;
		}

		void XboxControllerKeyEvent(WORD Button, bool Updown)
		{
			StageManager::GetGameGraphic()->GetGameStage()->XboxControllerKeyEvent(Button, Updown);
		}

		void deleteSelectPiece()
		{

			StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child;
			std::vector<ImageControl*>::iterator _itor = StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child.begin();

			while (_itor != StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child.end())
			{
				ImageControl* target = *_itor;
				if (target != NULL)
				{
					if (target->_currentName == _SelectID)
					{
						delete(target);
						_itor = StageManager::GetGameGraphic()->GetGameStage()->m_Container->m_Child.erase(_itor);
					}
					else
					{
						target->deleteSelectPiece(_SelectID);
						_itor++;
					}
				}
				
			}
		}

	};

}