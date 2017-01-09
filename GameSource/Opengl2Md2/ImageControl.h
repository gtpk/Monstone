#pragma once

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

using namespace std;
class ImageControl : public UIBase, public IEventHandler<ClickEventArgs> , MarxObject , public AnimationBase
{
public:
	float vertexBuffer[12];
	float textureBuffer[12];

	short index[6] = {
		0, 1, 2,
		0, 3, 2
	};

	string Name;

	int NowTextureId = 0;

	bool isWidthPercent;
	bool isHeightPercent;

	int Aligen;




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



	

	/////////////////////////////////////////////////////////////////
	/*  UIBase를 구현하기위하여 사용하는 변수들                                                    */
	/////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////


	ImageControl();
	ImageControl(string ObjName);
	ImageControl(string ObjName, float width, float height);

	virtual void eventReceived(UIBase* sender, ClickEventArgs e) { }

	void OnDraw();

	void setbeckgroundImage(string string);

	void setbeckgroundImage(string string, float width, float height);

};
