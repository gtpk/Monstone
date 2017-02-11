/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Md2Player.cpp -- Copyright (c) 2006-2007 David Henry
// last modification: may. 7, 2007
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Main file of the MD2 Loader.
//
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>    // std::sort
#include <cstdarg>
#include <cerrno>
#include <cmath>
#include <math.h>
#include "Opengl2md2.h"
#include "Texture.h"

#include "MarxWorld.h"
#include "TextureManager.h"
#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"

#include "CommonDataType.h"
#include "LuaManager.h"
#include "MotionEvent.h"
#include "ViewCamera.h"

#include "XBoxControllerManager.h"
#include "CollisionMapCreater.h"
#include "EyeMouseMove.h"
#include "ObjectMove.h"
#include "ObjectNumberingMananger.h"
using std::cout;
using std::cerr;
using std::endl;
using namespace MarxEngine;
// static 초기화는 이렇게 이루어지는것!
Opengl2md2 *Opengl2md2::inst = NULL;


Opengl2md2::Opengl2md2():
	bTextured(true),bLightGL(false),bAnimated(true),emTrancelate(EM_TRANCELATE),
	verbose(2),renderMode(0),frameRate(7),fps(0),hits(0),wheel(0.005),scale(0.1),bSelectMode(true)
	,bIsMouse_Left_Down(false), bIsMouse_Mid_Down(false)
{
	player = NULL;
	for(int i = 0 ; i < 3; i ++)
	{
		angle[i] = 0;
		trance[i] = 0;
	}

	mouse.buttons[0] = -1;
	mouse.buttons[1] = -1;
	mouse.buttons[2] = -1;


}
// --------------------------------------------------------------------------
// animMenu & skinMenu
//
// GLUT menu callback functions. Handle the menus. Select the skin
// to use and the animation to play.
// --------------------------------------------------------------------------

void Opengl2md2::animMenu (int item)
{
	inst->player->setAnim (inst->animList[item]);

	//glutPostRedisplay ();
}


void Opengl2md2::skinMenu (int item)
{
	inst->player->setSkin (inst->skinList[item]);

	//glutPostRedisplay ();
}


// -------------------------------------------------------------------------
// buildSkinMenu
//
// Create GLUT menu for skin selection.
// -------------------------------------------------------------------------

int Opengl2md2::buildSkinMenu (const Md2Model::SkinMap &skinMap)
{
	return 0;

	string skinName;
	int i = 0;

	Md2Model::SkinMap::const_iterator itor;
	for (itor = skinMap.begin (); itor != skinMap.end (); ++itor)
		skinList.push_back (itor->first);

	sort (skinList.begin (), skinList.end ());

	int menuId = glutCreateMenu (skinMenu);

	vector<string>::iterator it;
	for (it = skinList.begin (); it != skinList.end (); ++it)
	{
		skinName.assign (*it, it->find_last_of ('/') + 1, it->length ());
		glutAddMenuEntry (skinName.c_str (), i++);
	}

	return menuId;
}


// -------------------------------------------------------------------------
// buildSelectMenu
//
// Create GLUT menu for skin selection.
// -------------------------------------------------------------------------

int	Opengl2md2::buildSelectMenu (const Md2Model::SkinMap &skinMap)
{
	return 0;

	string skinName;
	int i = 0;

	Md2Model::SkinMap::const_iterator itor;
	for (itor = skinMap.begin (); itor != skinMap.end (); ++itor)
		skinList.push_back (itor->first);

	sort (skinList.begin (), skinList.end ());

	int menuId = glutCreateMenu (skinMenu);

	vector<string>::iterator it;
	for (it = skinList.begin (); it != skinList.end (); ++it)
	{
		skinName.assign (*it, it->find_last_of ('/') + 1, it->length ());
		glutAddMenuEntry (skinName.c_str (), i++);
	}

	return menuId;

}


// -------------------------------------------------------------------------
// buildAnimMenu
//
// Create GLUT menu for animation selection.
// -------------------------------------------------------------------------

int	Opengl2md2::buildAnimMenu (const Md2Model::AnimMap &animMap)
{

	int i = 0;

	Md2Model::AnimMap::const_iterator itor;
	for (itor = animMap.begin (); itor != animMap.end (); ++itor)
		animList.push_back (itor->first);

	sort (animList.begin (), animList.end ());

	int menuId = glutCreateMenu (animMenu);

	vector<string>::iterator it;
	for (it = animList.begin (); it != animList.end (); ++it)
		glutAddMenuEntry (it->c_str (), i++);

	return menuId;

	return 0;
}


// -------------------------------------------------------------------------
// shutdownApp
//
// Application termination.
// -------------------------------------------------------------------------

void	Opengl2md2::shutdownApp ()
{
	if(player != NULL)
		delete player;

	Texture2DManager::kill ();
}


// -------------------------------------------------------------------------
// init
//
// Application initialization.  Setup keyboard input, mouse input,
// timer, camera and OpenGL.
// -------------------------------------------------------------------------

void	Opengl2md2::init ()
{
	//
	// GLEW Initialization
	//



	GLenum err = glewInit ();
	if (GLEW_OK != err)
	{
		// Problem: glewInit failed, something is seriously wrong.
		//cerr << "Error: " << glewGetErrorString (err) << endl;
		MessageBox(m_hWnd,"Problem: glewInit failed, something is seriously wrong.","오류",MB_OK);
		shutdownApp ();
		exit (0);
	}

	//
	// Application initialization
	//

	// Initialize keyboard
	memset (keyboard.keymap, 0, 256);
	memset (keyboard.special, 0, 256);

	// Inititialize mouse
	mouse.buttons[GLUT_LEFT_BUTTON] = GLUT_UP;
	mouse.buttons[GLUT_MIDDLE_BUTTON] = GLUT_UP;
	mouse.buttons[GLUT_RIGHT_BUTTON] = GLUT_UP;
	mouse.x = 0;
	mouse.y = 0;

	// Initialize timer
	timer.current_time = 0;
	timer.last_time = 0;

	// Initialize camera input
	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;


	player = new MarxWorld ();

	//player->setScale (0.1f);


	if (isRealGameRun == false)
	{
		hPopupMenu = CreatePopupMenu();


		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 1, "맨 앞으로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 2, "앞으로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 3, "맨 뒤로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 4, "뒤로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 5, "삭제");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 6, "복제");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 7, "세트로 내보내기");

	}
	
	SetForegroundWindow(inst->m_hWnd);

	
	//
	// Initialize OpenGL
	//

	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel (GL_SMOOTH);

	glEnable (GL_DEPTH_TEST);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);

	glCullFace (GL_BACK);

	if (render == NULL)
		render = new GameStadiumScreen();
	render->onSurfaceCreated();
}

void Opengl2md2::StartGame()
{

}

void Opengl2md2::MenuFunc (int button)
{
	switch (button) {
	case 1:
		break;
	}
	glutPostRedisplay ();
}


// -------------------------------------------------------------------------
// reshape
//
// OpenGL window resizing.  Update the viewport and the projection matrix.
// -------------------------------------------------------------------------

void	Opengl2md2::reshape (int w, int h)
{


	if (h == 0)
		h = 1;
	glMatrixMode(GL_PROJECTION);

	inst->render->onSurfaceChanged(w, h);
	//ExGameGraphicInfo::GetGameGraphic()->SetGameSize(Point(w, h));
	inst->m_Width = w;
	inst->m_Hight = h;
}


// -------------------------------------------------------------------------
// updateTimer
//
// Update the timer.
// -------------------------------------------------------------------------

void	Opengl2md2::updateTimer (COMMONDATATYPE::glut_timer_t *t)
{
	t->last_time = t->current_time;
	t->current_time = glutGet (GLUT_ELAPSED_TIME) * 0.001f;
}


// -------------------------------------------------------------------------
// handleKeyboard
//
// Keyboard input handling.  Handle here continuous actions when a key
// is pressed (like moving the camera).
// -------------------------------------------------------------------------

void	Opengl2md2::handleKeyboard (COMMONDATATYPE::keyboard_input_t *k)
{
	/*
	if (k->keymap['yourkey'])
	do_something ();
	*/
}


// -------------------------------------------------------------------------
// begin2D
//
// Enter into 2D mode.
// -------------------------------------------------------------------------

void	Opengl2md2::begin2D ()
{
	//int width = glutGet (GLUT_WINDOW_WIDTH);
	//int height = glutGet (GLUT_WINDOW_HEIGHT);

	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();

	glLoadIdentity ();
	glOrtho (0, m_Width, 0, m_Hight, -1.0f, 10000.0f);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glEnable(GL_ALPHA_TEST); //투명 태스트 통과
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST );
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


// -------------------------------------------------------------------------
// end2D
//
// Return from 2D mode.
// -------------------------------------------------------------------------

void	Opengl2md2::end2D ()
{
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_BLEND);
	glMatrixMode (GL_PROJECTION);
	glPopMatrix ();
	glMatrixMode (GL_MODELVIEW);
}


// -------------------------------------------------------------------------
// glPrintf
//
// printf-like function for OpenGL.
// -------------------------------------------------------------------------

int Opengl2md2::glPrintf (const char *format, ...)
{
	char buffer[1024];
	std::va_list arg;
	int ret;

	// Format the text
	va_start (arg, format);
#ifndef _WIN32
	ret = std::vsnprintf (buffer, sizeof (buffer), format, arg);
#else
	ret = std::vsprintf (buffer, format, arg);
#endif

	va_end (arg);

	// Print it
	for (unsigned int i = 0; i < strlen (buffer); ++i)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, buffer[i]);

	return ret;
}


// -------------------------------------------------------------------------
// gameLogic
//
// Perform application logic.
// -------------------------------------------------------------------------

void	Opengl2md2::gameLogic ()
{
	// Calculate frame per seconds
	static double current_time = 0;
	static double last_time = 0;
	static int n = 0;

	n++;
	current_time = timer.current_time;

	LuaManager::Getinstance()->frameMove(current_time - last_time);

	if( (current_time - last_time) >= 1.0 )
	{
		fps = n;
		n = 0;
		last_time = current_time;
	}

	// Animate player
	if (bAnimated)
	{
		if(!player)
			return;
		double dt = timer.current_time - timer.last_time;
		player->animate (frameRate * dt);
	}

	




}




// -------------------------------------------------------------------------
// draw3D
// Render the 3D part of the scene.
// -------------------------------------------------------------------------

void Opengl2md2::draw3D ()
{

	//glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);
	//player->playerMesh()->setRotate(angle);
	
	// Clear window
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity ();
	
	
	// Perform camera transformations
	
	//glMatrixMode(GL_PROJECTION);
	//glOrtho(0, m_Width, 0, m_Hight, -1.0f, 1000.0f);
	glRotated (rot.x, 1.0f, 0.0f, 0.0f);
	glRotated (rot.y, 0.0f, 1.0f, 0.0f);
	glRotated (rot.z, 0.0f, 0.0f, 1.0f);
	Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

	glScaled((float)(GameSize.x / 1264.0f), (float)(GameSize.y / 682.0f), 1);

	glTranslated (-ViewCamera::getinstance()->eye.x, -ViewCamera::getinstance()->eye.y, -ViewCamera::getinstance()->eye.z);

	glScaled(ViewCamera::getinstance()->ViewScale, ViewCamera::getinstance()->ViewScale,1);

	glEnable (GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST); //튜명 태스트 통과
	glEnable( GL_BLEND );
	glAlphaFunc(GL_GREATER, 0); //뒤에 투명으로 투과

	if (bLightGL)
		glEnable (GL_LIGHTING);

	if (bTextured)
		glEnable (GL_TEXTURE_2D);
	glFrontFace(GL_CW);
	// Draw objects

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glRotatef( angle, 0.0, 1.0, 0.0 );
	
	player->drawPlayerItp (bAnimated,
		static_cast<Md2Object::Md2RenderMode>(renderMode));
	
	//player->drawPlayerFrame (10,
	//    static_cast<Md2Object::Md2RenderMode>(renderMode));
	ObjectMove::getinstance()->OnDraw();
	

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable (GL_TEXTURE_2D);
	glDisable (GL_DEPTH_TEST);
	glDisable (GL_LIGHTING);

	if (emTrancelate == EM_CREATE_COLLISION)
	{
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_BLEND);
		CollisionMapCreater::getinstance()->onDraw();
		

		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
	

	if(emTrancelate == EM_ROTAION && inst->bIsMouse_Left_Down)
	{
		Md2Object* obj = (Md2Object*)inst->player->FindSelectTopObj();

		if(obj != NULL)
		{
			float x1 = obj->getTranslate()[0];
			float y1 = obj->getTranslate()[1];

			float x2 = inst->a_mouse.x;
			float y2 = inst->a_mouse.y;


			glLineWidth(10);
			glColor3f(1.0f,1.0f,1.0f);

			//회전 안내선 그리기
			glBegin(GL_LINES);


			glVertex2f(x1, y1);
			glVertex2f(x2, y2);
			//		glVertex2f(4, -2);
			//		glVertex2f(7, 2);
			glDisable(GL_LINES);
			glEnd();
			glLineWidth(1);
		}


	}


}




// -------------------------------------------------------------------------
// draw2D
//
// Render the 2D part of the scene.
// -------------------------------------------------------------------------

void Opengl2md2::draw2D ()
{
	//begin2D();
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	//end2D();
	
	if (!inst->Close2d)
	{
		begin2D();
		//gluOrtho2D(0, 480, 800, 0);
		//glViewport(0, 0, 480, 800);
		//glOrtho(0, 480, 0, 800, -1.0f, 1.0f);
		glPushMatrix();
		//glTranslatef(dw, dh, zindex);

		inst->DetectXboxControllerButton();
		inst->render->onDrawFrame();
		glPopMatrix();
		end2D();
	}
	

	//////////////////////////////////////////


	glViewport(0, 0, static_cast<GLsizei>(inst->m_Width), static_cast<GLsizei>(inst->m_Hight));

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	glOrtho(0, m_Width, 0, m_Hight, -1.0f, 10000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//begin2D();
	glColor3f (1.0f, 1.0f, 1.0f);

	string currSkin, currAnim;

	currSkin = player->currentSkin ();
	currAnim = player->currentAnim ();

	currSkin.assign (currSkin, currSkin.find_last_of ('/') + 1,
		currSkin.length ());

	if (verbose > 0)
	{
		glRasterPos2i (10, 10);
		glPrintf ("FPS: %i", fps);
	}

	if (verbose > 1)
	{
		glRasterPos2i (10, m_Hight- 20);
		glPrintf ("Rendering player: \"%s\"", player->name ().c_str ());

		glRasterPos2i (10, m_Hight - 35);
		glPrintf ("Currently playing: \"%s\"", currAnim.c_str ());

		glRasterPos2i (10,m_Hight - 50);
		glPrintf ("Current skin: \"%s\"", currSkin.c_str ());

		glRasterPos2i (10,m_Hight - 65);
		glPrintf ("Frame rate: %i", frameRate);

		if(emTrancelate == EM_TRANCELATE)
		{
			glRasterPos2i (10, m_Hight - 80);
			glPrintf ("Translate Mode");
		}
		else if (emTrancelate == EM_ROTAION)
		{
			glRasterPos2i (10, m_Hight - 80);
			glPrintf ("Rotation Mode");
		}
		else if (emTrancelate == EM_SCALE)
		{
			glRasterPos2i (10, m_Hight - 80);
			glPrintf ("SCALE Mode (It's Not Ready)");
		}
		else if (emTrancelate ==EM_SELECT)
		{
			glRasterPos2i (10, m_Hight - 80);
			glPrintf ("Select Mode");
		}
		else if (emTrancelate == EM_CREATE_COLLISION)
		{
			glRasterPos2i(10, m_Hight - 80);
			glPrintf("Create Collistion Mode");
		}

		if(emTrancelate == EM_ROTAION)
		{
			glRasterPos2i (10, m_Hight - 95);
			glPrintf ("Rotation dgree : %.0f",inst->angle[2]);
		}
		if (inst->Close2d)
		{
			glRasterPos2i(10, m_Hight - 125);
			glPrintf("2D OFF X");
		}
		else
		{
			glRasterPos2i(10, m_Hight - 125);
			glPrintf("2D ON O");
		}
		
		glRasterPos2i (m_Width -150, m_Hight - 20);
		glPrintf ("Eye Position X: %f" , ViewCamera::getinstance()->eye.x);
		glRasterPos2i (m_Width -150, m_Hight - 35);
		glPrintf ("Eye Position Y: %f" , ViewCamera::getinstance()->eye.y);
		glRasterPos2i (m_Width -150, m_Hight - 50);
		glPrintf ("ViewScale : %f" , ViewCamera::getinstance()->ViewScale);

		glRasterPos2i (m_Width -150, m_Hight - 80);
		glPrintf ("Game Mouse X: %f" , inst->mouse.x);
		glRasterPos2i (m_Width -150, m_Hight - 95);
		glPrintf ("Game Mouse Y: %f" ,inst->mouse.y);
		//		glRasterPos2i (m_Width -150, m_Hight - 110);
		//		glPrintf ("Eye Position Z: %f" , inst->a_mouse.z);

		//inst->a_mouse
		glRasterPos2i (10, m_Hight - 110);
		if(ObjectMove::getinstance()->SelectObjectNum.size() > 0)
			glPrintf ("Select Object Name %d" , ObjectMove::getinstance()->SelectObjectNum[0]);
		else
			glPrintf("Select Object Name NONE");

	}

	//glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//end2D ();

	
}

void Opengl2md2::ProcessSelect(GLuint index[128])  // NEW //
{
	if (inst->keyboard.special[VK_SPACE] == true)
		return;

	int counting = 0;
	//새롭게 선택된 객체들
	std::vector<SelectObj> SelectList;
	{

		GLuint names, *ptr;

		printf("hits = %d\n", hits);
		ptr = (GLuint *)index;
		for (int i = 0; i < hits; i++) {  /* for each hit  */
			SelectObj s;
			names = *ptr;
			s.names = names;
			printf(" number of names for hit = %d\n", names); ptr++;
			s.z1 = *ptr;
			printf("  z1 is %g;", (float)*ptr / 0x7fffffff); ptr++;
			s.z2 = *ptr;
			printf(" z2 is %g\n", (float)*ptr / 0x7fffffff); ptr++;

			printf("   the name is ");
			for (int j = 0; j < names; j++) {  /* for each name */
				printf("%d ", *ptr);
				s.index[j] = (*ptr);
				ptr++;
				counting++;
			}
			printf("\n");
			if(names != 0)
				SelectList.push_back(s);
		}
	}

	if (inst->Close2d)
	{
		// 모두 해재한후
		for (int i = 0; i < ObjectMove::getinstance()->SelectObjectNum.size(); i++)
		{
			player->setSelectObj(ObjectMove::getinstance()->SelectObjectNum[i], false);
			inst->render->setSelectObj(ObjectMove::getinstance()->SelectObjectNum[i],false);
		}

		//선택이 없으면 다지움
		if (SelectList.size() == 0)
		{
			ObjectMove::getinstance()->SelectObjectNum.clear();
			if (MarxWorld::getInstance().Volkes != NULL)
				MarxWorld::getInstance().Volkes->SetMd2ObjectSelection(NULL);
		}
		else
		{
			// 맨 위에 객체만 선택한다. 
			// 이름이 없는 객체는 이미 배제되어있다.
			if (inst->keyboard.special[VK_CONTROL])
			{

				player->setSelectObj(SelectList[SelectList.size() - 1].index[0], true);

				//등록된것들 다 다시 등록
				for (int i = 0; i < ObjectMove::getinstance()->SelectObjectNum.size(); i++)
				{
					player->setSelectObj(ObjectMove::getinstance()->SelectObjectNum[i], true);
				}
				bool isExsist = false;
				for (int i = 0; i < ObjectMove::getinstance()->SelectObjectNum.size(); i++)
				{
					if (SelectList[SelectList.size() - 1].index[0] == ObjectMove::getinstance()->SelectObjectNum[i])
					{
						isExsist = true;
					}
				}
				if (isExsist == false)
				{
					
					//새로운 객체를 추가한다.
					ObjectMove::getinstance()->SelectObjectNum.push_back(SelectList[SelectList.size() - 1].index[0]);
				}
				else
				{
					for (std::vector<int>::iterator i = ObjectMove::getinstance()->SelectObjectNum.begin();
						i != ObjectMove::getinstance()->SelectObjectNum.end(); i++)
					{
						if (*i == SelectList[SelectList.size() - 1].index[0])
						{
							ObjectMove::getinstance()->SelectObjectNum.erase(i);
							break;
						}
					}
					player->setSelectObj(SelectList[SelectList.size() - 1].index[0], false);
				}
			}
			else
			{

				player->setSelectObj(SelectList[SelectList.size() - 1].index[0], true);
				//새로 선택했으므로 선택리스트를 비운다.
				//ObjectMove::getinstance()->SelectObjectNum.clear();
				bool isExsist = false;
				for (int i = 0; i < ObjectMove::getinstance()->SelectObjectNum.size(); i++)
				{
					if (SelectList[SelectList.size() - 1].index[0] == ObjectMove::getinstance()->SelectObjectNum[i])
					{
						isExsist = true;
					}
				}
				if (isExsist == false)
				{
					ObjectMove::getinstance()->SelectObjectNum.clear();
					ObjectMove::getinstance()->SelectObjectNum.push_back(SelectList[SelectList.size() - 1].index[0]);
				}
				//등록된것들 다 다시 등록
				for (int i = 0; i < ObjectMove::getinstance()->SelectObjectNum.size(); i++)
				{
					player->setSelectObj(ObjectMove::getinstance()->SelectObjectNum[i], true);
				}
			}

			//최초 선택된 것만 체크한다.
			Md2Object* obj = NULL;
			if (ObjectMove::getinstance()->SelectObjectNum.size() != 0)
			{
				obj = (Md2Object*)MarxWorld::getInstance().FindbyNameObj(
					ObjectMove::getinstance()->SelectObjectNum[0]);
			}
			if (obj != NULL)
			{

				if (MarxWorld::getInstance().Volkes != NULL)
					MarxWorld::getInstance().Volkes->SetMd2ObjectSelection(obj);

			}

			ObjectMove::getinstance()->old_mouse = inst->a_mouse;
		}
		
	}
	else
	{
		//if (hits == 0)
		//{
		//	//ObjectMove::getinstance()->SelectObjectNum = -1;
		//	inst->render->setSelectObj(ObjectMove::getinstance()->SelectObjectNum[0]);
		//
		//}
		//else
		//{
		//	ObjectMove::getinstance()->SelectObjectNum = index[(4 * hits) - 1];
		//	inst->render->setSelectObj(ObjectMove::getinstance()->SelectObjectNum);
		//	ImageControl* node = inst->render->FindSelectTopObj();
		//	if (MarxWorld::getInstance().Volkes != NULL)
		//		MarxWorld::getInstance().Volkes->SetImageControlSelection(node);
		//
		//
		//	
		//	//inst->render->onDrawFrame();
		//
		//}
	}
	
	/*
	switch(index[3]) {
	case 100:SelectObjectNum = 100; break;
	case 101:SelectObjectNum = 100; break;
	case 102:SelectObjectNum = 100; break;
	case 103:SelectObjectNum = 100; break;
	case 104: MessageBox(hWnd, "Cyan Solid Sphere", "Selection", MB_OK); break;
	case 105: MessageBox(hWnd, "Line", "Selection", MB_OK); break;

	default: MessageBox(hWnd, "What?", "Selection", MB_OK); break;
	}
	*/
}

void Opengl2md2::SelectObjects(GLint x, GLint y)
{
	//inst->Close2d

	if (inst->Close2d)
	{
		GLuint selectBuff[128];
		GLint viewport[4];

		glSelectBuffer(128, selectBuff);
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glRenderMode(GL_SELECT);
		glLoadIdentity();
		gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);
		glOrtho(0, inst->m_Width,
			0, inst->m_Hight, -10.0, 10000.0);
		glMatrixMode(GL_MODELVIEW);
		draw3D();
		glLoadIdentity();
		//glutPostRedisplay ();

		hits = glRenderMode(GL_RENDER);
		//if(hits>0) 
		ProcessSelect(selectBuff);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

		
	}
	else
	{
		GLuint selectBuff[64];
		GLint viewport[4];
		begin2D();
		glRasterPos2i(0, 0);
		glSelectBuffer(64, selectBuff);
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glRenderMode(GL_SELECT);
		glLoadIdentity();
		
		gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);
		glOrtho(0, inst->m_Width, 0, inst->m_Hight, -1.0f, 1000.0f);
		glMatrixMode(GL_MODELVIEW);
		inst->render->onDrawFrame();
		glLoadIdentity();
		//glutPostRedisplay ();

		hits = glRenderMode(GL_RENDER);
		//if(hits>0) 
		ProcessSelect(selectBuff);
		
		glPopMatrix();
		end2D();

		glMatrixMode(GL_PROJECTION);

		glMatrixMode(GL_MODELVIEW);

	}
	reshape(inst->m_Width, inst->m_Hight);
}

// -------------------------------------------------------------------------
// display
//
// Render the main scene to the screen.
// -------------------------------------------------------------------------

void Opengl2md2::display ()
{
	//wglMakeCurrent(inst->m_hDC, inst->m_hRC);
	glClear(GL_COLOR_BUFFER_BIT/* | GL10.GL_DEPTH_BUFFER_BIT*/);
	inst->gameLogic ();

	glPushMatrix();
	inst->draw3D ();

	glPopMatrix();
	glPushMatrix();
	inst->draw2D ();
	glPopMatrix();

	
	//glutSwapBuffers ();
	//SwapBuffers(inst->m_hDC);
	//wglMakeCurrent(NULL,NULL);
}


// -------------------------------------------------------------------------
// keyPress
//
// Key press glut callback function.  Called when user press a key.
// -------------------------------------------------------------------------

void Opengl2md2::keyPress (unsigned char key, int x, int y)
{
	LuaManager* pluaman = LuaManager::Getinstance();	
	int value = lua_tinker::call<int>(pluaman->NowStatus, "KeyDown", key);

	//printf("%d --> Keydown\n", value);

	// Update key state
	inst->keyboard.keymap[key] = 1;



	// 
	// Handle here ponctual actions when
	// a key is pressed (like toggle ligthing)
	// 

	// Escape

	//if (key == 27)
	//		exit (0);

	//if (key == 'a' || key == 'A')
	//	inst->bAnimated = !inst->bAnimated;

	//if (key == 'l' || key == 'L')
	//		bLightGL = !bLightGL;

	//if (key == 'r' || key == 'r')
	//	inst->renderMode = (inst->renderMode + 1) % 2;

	if (key == 's' || key == 'S')
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	//if (key == 't' || key == 'T')
	//	bTextured = !bTextured;

	//if (key == 'v' || key == 'V')
	//		inst->verbose = (inst->verbose + 1) % 4;

	if (key == 'w' || key == 'W')
		inst->emTrancelate = EM_TRANCELATE;
	//glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	//glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	if (key == '+')
		inst->frameRate++;

	if (key == '-')
		inst->frameRate--;

	//if (key == 't' || key == 'T')
	//	inst->emTrancelate = true;
	if (key == 'e' || key == 'E')
		inst->emTrancelate = EM_ROTAION;

	if (key == 'r' || key == 'R')
		inst->emTrancelate = EM_SCALE;

	if (key == 'q' || key == 'Q')
		inst->emTrancelate = EM_SELECT;

	if (key == 'o' || key == 'O')
		inst->emTrancelate = EM_CREATE_COLLISION;
	//  inst->bSelectMode = !inst->bSelectMode;

	if (key == '2')
		inst->Close2d = !inst->Close2d;



	if (inst->frameRate < 0)
		inst->frameRate = 0;

	if (key == VK_DELETE)
	{
		if (inst->Close2d)
		{
			inst->player->deleteSelectPiece();
		}
		else
		{
			inst->render->deleteSelectPiece();
		}
	}
		

	if(inst->keyboard.special[VK_LCONTROL] || inst->keyboard.special[VK_RCONTROL] )
	{
		if (key == 'C' || key == 'c')
		{
			inst->player->setSelectionCopy();
			//복사
		}
	}

	if (inst->keyboard.special[VK_LCONTROL] || inst->keyboard.special[VK_RCONTROL])
	{
		if (key == 'D' || key == 'd')
		{
			if (inst->Close2d)
			{
				inst->player->setSelectObj(-1);
			}
			else
			{
				inst->render->setSelectObj(-1);
			
			}
		}
	}

	if(inst->keyboard.special[VK_LCONTROL] || inst->keyboard.special[VK_RCONTROL] )
	{
		if (key == 'V' || key == 'v')
		{
			inst->player->setSelectionPaste();
			//붙여넣기
		}
	}

	if(inst->keyboard.special[VK_LCONTROL] || inst->keyboard.special[VK_RCONTROL] )
	{
		if (key == 'X' || key == 'x')
		{
			//잘라내기
		}
	}

	//glutPostRedisplay ();
}


// -------------------------------------------------------------------------
// keyUp
//
// Key up glut callback function.  Called when user release a key.
// -------------------------------------------------------------------------

void	Opengl2md2::keyUp (unsigned char key, int x, int y)
{
	LuaManager* pluaman = LuaManager::Getinstance();	
	int value = lua_tinker::call<int>(pluaman->NowStatus, "KeyUp", key);

	inst->keyboard.keymap[key] = 0;
}


// -------------------------------------------------------------------------
// specialKeyPress
//
// Key press glut callback function.  Called when user press a special key.
// -------------------------------------------------------------------------

void	Opengl2md2::specialKeyPress (int key, int x, int y)
{
	inst->keyboard.special[key] = 1;

	if (key == VK_SPACE && inst->Close2d)
	{
		EyeMouseMove::getinstance()->Enable();
	}

}


// -------------------------------------------------------------------------
// specialKeyUp
//
// Key up glut callback function.  Called when user release a special key.
// -------------------------------------------------------------------------

void	Opengl2md2::specialKeyUp (int key, int x, int y)
{
	if (key == VK_SPACE)
	{
		EyeMouseMove::getinstance()->Disable();
	}

	inst->keyboard.special[key] = 0;
}


// -------------------------------------------------------------------------
// mouseMotion
//
// Mouse motion glut callback function.  Called when the user move the
// mouse. Update the camera.
// -------------------------------------------------------------------------

void	Opengl2md2::mouseMotion (int x, int y)
{
	// Ahhhhh.. this is too difficult..
	Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();
	float realposx = x;
	//1. i'm not sure Logic, but Y(Hight) is UpsideDown
	float realposy = inst->m_Hight - y;
	//2. Multiply by Reciprocal of Resulution 
	realposx = realposx / (float)(GameSize.x / 1264.0f);
	realposy = realposy / (float)(GameSize.y / 682.0f);
	//3. Add Carmera Translate
	if (inst->Close2d == true)
	{
		realposx += ViewCamera::getinstance()->eye.x;
		realposy += ViewCamera::getinstance()->eye.y;
	
		//4. Multiply  by Reciprocal of Scale  
		realposx /= ViewCamera::getinstance()->ViewScale;
		realposy /= ViewCamera::getinstance()->ViewScale;
	}
	//this is your Acture Mouse Positon


	inst->a_mouse.x = realposx;
	inst->a_mouse.y = realposy;

	
	

	if(inst->bIsMouse_Left_Down == true)
	{
		if (inst->keyboard.special[VK_SPACE] != true )
		{

			if (inst->Close2d == false)
			{

				ImageControl* obj = (ImageControl*)inst->render->FindSelectTopObj();
				if (obj == NULL)
					return;

				if (inst->emTrancelate == EM_TRANCELATE)
				{
					//inst->trance[0] = ObjectMove::getinstance()->old_trance[0] + ((realposx - ObjectMove::getinstance()->old_mouse.x));
					//inst->trance[1] = ObjectMove::getinstance()->old_trance[1] + ((realposy - ObjectMove::getinstance()->old_mouse.y));
					obj->x = inst->trance[0];
					obj->y = inst->trance[1];
				}
			}
			else
			{
				Md2Object* obj = (Md2Object*)inst->player->FindSelectTopObj();
				if (obj != NULL)
				{
					if (inst->emTrancelate == EM_TRANCELATE)
					{
						COMMONDATATYPE::mouse_input_t mouse;
						mouse.x = realposx;
						mouse.y = realposy;
						for (int i = 0; i < ObjectMove::getinstance()->SelectObjectNum.size(); i++)
						{
							
							SelectableObject* node = dynamic_cast<SelectableObject*>(ObjectNumberingMananger::getInstance()->GetMarxObject(
								ObjectMove::getinstance()->SelectObjectNum[i]));
							if (node != NULL)
								node->Dragging(mouse);
						}
						
						MarxWorld::getInstance().Volkes->SelectedObjectChanged();
					}
					else if (inst->emTrancelate == EM_ROTAION)
					{

						float x1 = obj->getTranslate()[0];
						float y1 = obj->getTranslate()[1];

						float x2 = inst->a_mouse.x;
						float y2 = inst->a_mouse.y;

						float ax = x1 - x2;
						float ay = y1 - y2;

						if (ax == 0 || ay == 0)
							return;

						//float ac = (ay) / (ax);

						float radian = atan2(ay, ax);

						// 근사치로 계산함.
						float dgree = radian / 3.14159 * 180;


						// Rotation
						inst->angle[2] = dgree;//+ inst->old_dgree;

						if (inst->angle[2] < 0.0)
							inst->angle[2] += 360.0;

						if (inst->angle[2] > 360.0)
							inst->angle[2] -= 360.0;

						inst->player->setRotate(inst->angle);




					}
					else if (inst->emTrancelate == EM_SCALE)
					{
						int powx = (x - inst->mouse.x) * (x - inst->mouse.x);
						int powy = (y - inst->mouse.y) * (y - inst->mouse.y);

						GLfloat distance = sqrt(powx + powy);

						inst->scale = distance;

						inst->player->setScale(inst->scale);

					}
				}
					

				
			}
			
		}
	}
	if(inst->bIsMouse_Right_Down == true)
	{

	}


	if (inst->mouse.buttons[GLUT_MIDDLE_BUTTON] == GLUT_DOWN)
	{
		inst->bIsMouse_Mid_Down = true;

	
	}
	else if(inst->mouse.buttons[GLUT_MIDDLE_BUTTON] == GLUT_UP)
	{
		inst->bIsMouse_Mid_Down = false;
	}


	if (inst->mouse.buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)
	{

		if (inst->Close2d)
		{
			
			
			

			if (inst->keyboard.special[VK_SPACE] != true)
			{
				if (inst->emTrancelate == EM_CREATE_COLLISION)
				{
					
					CollisionMapCreater::getinstance()->SetVertext(realposx, realposy);
				}
				else
				{
					inst->SelectObjects(x, y);
				}
			}
			

			if (inst->emTrancelate == EM_ROTAION)
			{
				Md2Object* obj = (Md2Object*)inst->player->FindSelectTopObj();

				if (obj == NULL)
					return;

			}
			
			

		}
		else
		{
			inst->SelectObjects(x, y);

			if (inst->keyboard.special[VK_SPACE] != true)
			{
				ImageControl* obj = (ImageControl*)inst->render->FindSelectTopObj();

				if (obj == NULL)
					return;

				inst->old_trance[0] = obj->x;
				inst->old_trance[1] = obj->y;
				inst->old_trance[2] = obj->zindex;

				inst->mouse.x = x;
				inst->mouse.y = y;

			}
		}
		
		inst->mouse.x = realposx;
		inst->mouse.y = realposy;

		inst->bIsMouse_Left_Down = true;

	}
	else if(inst->mouse.buttons[GLUT_LEFT_BUTTON] == GLUT_UP)
	{
		inst->bIsMouse_Left_Down = false;
	}


	if (inst->mouse.buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
	{



		inst->SelectObjects(x, y);

		POINT pt;
		GetCursorPos(&pt);


		TrackPopupMenu(inst->hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x, pt.y, 0, inst->m_hWnd, NULL);

		inst->bIsMouse_Right_Down = true;
	}
	else if(inst->mouse.buttons[GLUT_RIGHT_BUTTON] == GLUT_UP)
	{
		inst->bIsMouse_Right_Down = false;
	}



	EyeMouseMove::getinstance()->SetMousePos(x,y, inst->bIsMouse_Left_Down);



	//glutPostRedisplay ();
}



void Opengl2md2::menuSelect(HMENU menu, int idx)
{
	if (menu == 0)
	{
		/*
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING , 1, "맨 앞으로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 2, "앞으로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 3, "맨 뒤로 보내기");
		InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 4, "뒤로 보내기");
		*/
		switch (idx)
		{
		case 1:
			inst->player->setSelectionTopMost();
			break;
		case 2:
			inst->player->setSelectionTop();
			break;
		case 3:
			inst->player->setSelectionBottomMost();
			break;
		case 4:
			inst->player->setSelectionBottom();
			break;
		case 5:
			inst->player->deleteSelectPiece();
			break;
		case 6:
			inst->player->duplicateSelectPiece();
			break;
		case 7:
			inst->player->CreateSet();
		default:
			break;
		}
	}
}


// -------------------------------------------------------------------------
// mouseButton
//
// Mouse button press glut callback function.  Called when the user
// press a mouse button. Update mouse state and keyboard modifiers.
// -------------------------------------------------------------------------

void Opengl2md2::mouseButton (int button, int state, int x, int y)
{
	EyeMouseMove::getinstance()->Last_mouse.x = x;
	EyeMouseMove::getinstance()->Last_mouse.y = y;


	// Update key modifiers
	inst->keyboard.modifiers = glutGetModifiers ();

	// Update mouse state
	inst->mouse.buttons[button] = state;

	Point GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

	MotionEvent _e;
	inst->m_Width;
	_e.x = x * (float)(ExGameGraphicInfo::GetGameGraphic()->GetGameSize().x / inst->m_Width);
	_e.y = (inst->m_Hight - y) * (float)(ExGameGraphicInfo::GetGameGraphic()->GetGameSize().y/ inst->m_Hight);
	_e.state = state;
	_e.button = button;
	inst->render->onTouchEvent(_e);

	// 마우스 다운은 바로 처리하는게 인지 상정!

	if(inst->isRealGameRun == false)
		Opengl2md2::mouseMotion(x,y);



	//그리고 초기화.
	inst->mouse.buttons[0] = -1;
	inst->mouse.buttons[1] = -1;
	inst->mouse.buttons[2] = -1;

}


void Opengl2md2::WhellScrolle (int PressKey, short Wheel)
{
	//if(Wheel > 0)
	if (Wheel / 120 > 1)
	{
		
		ViewCamera::getinstance()->ViewScale -= (Wheel % 120)*0.01;
	}
	else
	{
		float before = ViewCamera::getinstance()->ViewScale;
		ViewCamera::getinstance()->ViewScale += (Wheel / 120)*0.01;

		float diff = before - ViewCamera::getinstance()->ViewScale;
		ViewCamera::getinstance()->eye.x -= ((float)inst->m_Width* diff)/2;
		ViewCamera::getinstance()->eye.y -= ((float)inst->m_Hight* diff)/2;
		//inst->eye.z += (Wheel / 120);
	}
	

}



// -------------------------------------------------------------------------
// idleVisible
//
// Idle glut callback function.  Continuously called. Perform background
// processing tasks.
// -------------------------------------------------------------------------

void	Opengl2md2::idleVisible ()
{
	// Update the timer
	inst->updateTimer (&inst->timer);

	// Handle keyboard input
	inst->handleKeyboard (&inst->keyboard);
	/*
	if (inst->bAnimated)
	glutPostRedisplay ();
	*/
}


// -------------------------------------------------------------------------
// windowStatus
//
// Window status glut callback function.  Called when the status of
// the window changes.
// -------------------------------------------------------------------------

void	Opengl2md2::windowStatus (int state)
{

	// Disable rendering and/or animation when the
	// window is not visible
	if ((state != GLUT_HIDDEN) &&
		(state != GLUT_FULLY_COVERED))
	{
		glutIdleFunc (idleVisible);
	}
	else
	{
		glutIdleFunc (NULL);
	}

}


// -------------------------------------------------------------------------
// main
//
// Application main entry point.
// -------------------------------------------------------------------------

int Opengl2md2::Openflmd2init (int argc, char *argv[], HDC hdc, HGLRC hRC,HWND hwnd)
{
	// Initialize GLUT
	glutInit (&argc, argv);

	m_hRC = hRC;
	m_hDC = hdc;
	m_hWnd = hwnd;

	init ();


	return 0;
}

int Opengl2md2::Monstoneinit(int argc, char *argv[], HDC hdc, HGLRC hRC, HWND hwnd)
{
	ExGameGraphicInfo::GetGameGraphic()->SetGameSize(Point(1280, 700));
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitWindowSize(ExGameGraphicInfo::GetGameGraphic()->GetGameSize().x, ExGameGraphicInfo::GetGameGraphic()->GetGameSize().y);
	isRealGameRun = true;
	m_hRC = hRC;
	m_hDC = hdc;
	m_hWnd = hwnd;

	init();
	StartGame();
	
	return 0;
}




void Opengl2md2::SetNewPiece()
{

}


void Opengl2md2::Save()
{
	if (inst->Close2d)
	{
		MarxWorld::getInstance().Save();
	}
	else
	{
		StageManager::GetGameGraphic()->GetGameStage()->Save();
	}
	
}

void Opengl2md2::Load(string sModelname)
{
	if (inst->Close2d)
	{
		MarxWorld::getInstance().Load(sModelname);
	}
	else
	{
		StageManager::GetGameGraphic()->GetGameStage()->Load(sModelname);
	}
}

void Opengl2md2::DetectXboxControllerButton()
{
	for (int i = 0; i < 4; i++)
	{
		CXBOXController* player = XBoxControllerManager::getinstance()->getController(i);
		if (player->IsConnected())
		{
			XINPUT_STATE newData = player->GetState();
			if (Gamepad[i].Gamepad.wButtons != newData.Gamepad.wButtons)
			{
				WORD CheckSum = Gamepad[i].Gamepad.wButtons ^ newData.Gamepad.wButtons;
				for (int check = 1; check <  65535; check <<=1)
				{
					if ((CheckSum & check) != 0)
					{
						//printf("Changed %X ", check);
						bool Updown = false;
						if ((check & newData.Gamepad.wButtons )== 0)
						{
							//printf("UP");
							Updown = true;
						}
						else
						{
							Updown = false;
							//printf("Down");
						}
						render->XboxControllerKeyEvent(check, Updown);
						//printf("\n");
					}
				}
			}

			Gamepad[i] = newData;
		}
	}
}