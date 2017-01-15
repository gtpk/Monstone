#pragma once

#include "GL/glew.h"
#include "GL/glut.h"

#include "MarxWorld.h"
#include "TextureManager.h"
#include "CommonDataType.h"
#include "../Common/VolkesInterface.h"
#include "LuaManager.h"
#include "GameStadiumScreen.h"
#include "KardNameFactory.h"

class Opengl2md2
{
private :
	COMMONDATATYPE::mouse_input_t mouse;

	COMMONDATATYPE::mouse_input_t a_mouse;

	COMMONDATATYPE::keyboard_input_t keyboard;
	
	COMMONDATATYPE::glut_timer_t timer;

	HGLRC					m_hRC;
	HDC						m_hDC;
	HWND					m_hWnd;
	// PopUp �޴� Wnd��.
	HMENU					hPopupMenu ;

	MarxWorld *player;

	COMMONDATATYPE::Vector3d rot;

	GameStadiumScreen * render = NULL;

	enum EnumNowAction
	{
		EM_TRANCELATE,
		EM_ROTAION,
		EM_SCALE,
		EM_SELECT,
	};

	bool bTextured;
	bool bLightGL;
	bool bAnimated;
	EnumNowAction emTrancelate;
	bool bSelectMode;

	bool bIsMouse_Mid_Down;
	bool bIsMouse_Left_Down;
	bool bIsMouse_Right_Down;

	int verbose;
	int renderMode;
	int frameRate;
	int fps;

	float wheel;

	int m_Width,m_Hight;

	int SelectObjectNum;

	
	GLint hits;

	GLfloat ratio; // NEW //
	GLfloat old_dgree;

	vec3_t			angle;
	vec3_t			trance;
	vec3_t			old_trance;

	GLfloat scale;

	vector<string> skinList;
	vector<string> animList;


	GLfloat ViewScale = 1;

	Opengl2md2();

	static Opengl2md2 *inst;
	
public:

	COMMONDATATYPE::Vector3d eye;


	
	static Opengl2md2& getInstance()
	{
		if(inst == NULL)
		{
			inst = new Opengl2md2();
		}
		return *inst;
	}

public :
	static void animMenu (int item);
	static void skinMenu (int item);
	void shutdownApp ();
	void init ();
	static void reshape (int w, int h);

	void updateTimer (COMMONDATATYPE::glut_timer_t *t);
	void handleKeyboard (COMMONDATATYPE::keyboard_input_t *k);
	void begin2D ();
	void end2D ();
	int glPrintf (const char *format, ...);
	void gameLogic ();
	void draw3D ();
	void draw2D ();
	static void display ();
	static void keyPress (unsigned char key, int x, int y);
	static void keyUp (unsigned char key, int x, int y);
	static void specialKeyPress (int key, int x, int y);
	static void specialKeyUp (int key, int x, int y);
	static void mouseMotion (int x, int y);
	static void mouseButton (int button, int state, int x, int y);
	static void WhellScrolle (int PressKey, short Wheel);
	static void idleVisible ();
	static void windowStatus (int state);
	static void menuSelect(HMENU menu, int idx);
	
public:

	int Openflmd2init(int argc, char *argv[], HDC hdc, HGLRC hRC,HWND hwnd);
	int	buildSkinMenu (const Md2Model::SkinMap &skinMap);
	int	buildSelectMenu (const Md2Model::SkinMap &skinMap);
	int	buildAnimMenu (const Md2Model::AnimMap &animMap);
	void ProcessSelect(GLuint index[64]) ;
	void SelectObjects(GLint x, GLint y);

	void SetNewPiece();
	void MenuFunc (int button);
};