#pragma once
#include <Windows.h>

#include <string>
#include <vector>
#include "PointF.h"
#include "UIBase.h"
#include "IEventHandler.h"
#include "Animation.h"
#include "Atlasobj.h"
#include "ClickEventArgs.h"
#include "KardNameFactory.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "TextureManager.h"
#include "ExGameGraphicInfo.h"
#include "defAnimations.h"
#include "AnimatinonBase.h"
#include "PointF.h"
#include "IContainer.h"

using namespace std;
class ImageControl : 
	public UIBase,
	public IEventHandler<ClickEventArgs> ,
	MarxObject , 
	public AnimationBase,
	public IContainer
{
public:
	GLfloat vertexBuffer[15] = {
		0.0f	, 800.0f	, 0.0f, // 0, Left Top
		480.0f	, 800.0f	, 0.0f,	// 1, Right Top
		480.0f	, 0.0f	, 0.0f,	// 2, Right Bottom
		0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
		0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
	};
	float uv_x = 0.46875f;
	float uv_y = 0.78125f;
	GLfloat textureBuffer[15] = {
		0.0f ,uv_y ,
		uv_x , uv_y ,
		uv_x , 0.0f ,
		0.0f, 0.0f  ,
		0.0f, 0.0f  ,
	};

	unsigned short index[6] = {
		0,1,2,
		0,2,3
	};

	string Name;

	int NowTextureId = 1;

	bool isWidthPercent;
	bool isHeightPercent;

	bool NotExsistImage = true;
	int Aligen;

	float zindex = 0;


	bool IsVerticalReverse = false;

	float ScaleX = 1;
	float ScaleY = 1;

	string TextureName = "";

	bool isIsVerticalReverse() {
		return IsVerticalReverse;
	}

	void setIsVerticalReverse(bool isVerticalReverse) {
		IsVerticalReverse = isVerticalReverse;
	}

protected:
	vector<ImageControl*> m_Child;

public:

public:
	void addChild(ImageControl* child)
	{
		m_Child.push_back(child);
	}

	virtual vector<ImageControl*> getAllChild();



public:
	// Note! 리스트에서만 지워진다. 객체는 지우지 않는다!
	void Remove(ImageControl* child);

public:
	bool AllAnimationFinished();

public:

	/////////////////////////////////////////////////////////////////
	/*  UIBase를 구현하기위하여 사용하는 변수들                                                    */
	/////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////


	ImageControl();
	ImageControl(string ObjName);
	ImageControl(string ObjName, float width, float height);

	virtual void eventReceived(UIBase* sender, ClickEventArgs e) { }

	void OnDraw(bool isSelect = false);

	

	void setbeckgroundImage(string string);

	void setbeckgroundImage(string string, float width, float height);


	void OnActualDraw();

};
