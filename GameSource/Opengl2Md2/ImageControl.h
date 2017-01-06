#pragma once

#include <string>
#include <vector>
#include "PointF.h"
#include "IUIBase.h"
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

using namespace std;
class ImageControl : PointF, IUIBase, IEventHandler<ClickEventArgs>
{
public:
	float vertexBuffer[12];
	short indexBuffer[12];
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

	bool visiable = true;



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

	bool isNotClickable;

	vector<Animation*> animations;

	void SetAnimation(Animation* _ani)
	{
		/*
		Iterator<Animation> iter = animation.iterator();
		while(iter.hasNext())
		{
		Animation contator = (Animation)iter.next();

		if( contator.mType == _ani->mType)
		{
		iter.remove();
		//return;
		}
		}
		*/

		animations.push_back(_ani);
	}

	void RemoveAnimation(Type _aniType)
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;

			if (contator->mType == _aniType)
			{
				iter= animations.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void AnimationPlay()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			contator->Play();
			iter++;
		}
	}

	void AnimationPause()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			contator->Pause();
			iter++;
		}
	}

	void AnimationRemoveAll()
	{
		//if(animation.size() == 0)
		//	return;
		animations.clear();
		/*
		Iterator<Animation> iter = animation.iterator();
		while(iter.hasNext())
		{
		iter.remove();
		}*/
	}

	bool AnimationisEnded()
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			if (contator->isEnded() == false)
				return false;
			iter++;
		}
		return true;
	}

	void SetAnimationDuration(long duration)
	{
		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* contator = (Animation*)*iter;
			contator->mDuration = duration;
			iter++;
		}
	}

	/////////////////////////////////////////////////////////////////
	/*  IUIbase를 구현하기위하여 사용하는 변수들                                                    */
	/////////////////////////////////////////////////////////////////

	UIVertical::Aligen_Vertical m_Aligen_Vertical;
	UIHorizen::Aligen_Horizen m_Aligen_Horizen;
	Point m_gridNum;
	Point m_gridSize;

	PointF m_Size;

	float _Acturalx;
	float _Acturaly;

	bool isCaculated;


	/////////////////////////////////////////////////////////////////


	ImageControl()
	{
		m_Aligen_Vertical = UIVertical::Aligen_Vertical::defalt;
		m_Aligen_Horizen = UIHorizen::Aligen_Horizen::defalt;

		m_gridNum = Point(0, 0);

		isNotClickable = false;
		isWidthPercent = true;
		isHeightPercent = true;
		_Acturalx = 0;
		_Acturaly = 0;
		isCaculated = false;

	}

	ImageControl(string ObjName)
	{

		setbeckgroundImage(ObjName);

	}


	ImageControl(string ObjName, float width, float height)
	{

		setbeckgroundImage(ObjName, width, height);

	}



	float getWidth()
	{
		return m_Size.x;
	}

	float getHeight()
	{
		return m_Size.y;
	}

	//@Override
	void SetWidth(float width) 
	{

		if (m_Size.x == width)
			return;

		m_Size.x = (int)width;
	}

	//@Override
	void SetHeight(float height) 
	{

		if (m_Size.y == height)
			return;

		if (m_Size.x == 0)
			m_Size.x = getWidth();

		m_Size.y = (int)height;
	}

	float Mouse_x = 0;
	float Mouse_y = 0;

	float minimum_x = 0;
	float minimum_y = 0;

	float total_x = 0;
	float total_y = 0;

	bool isPrang(MotionEvent e, int pointCount)
	{
		if (visiable == false)
			return false;

		if (isNotClickable == true)
			return false;

		// this.x > evnet.getX >  this.x + getWidth();

		float resolution = ExGameGraphicInfo::GetGameGraphic()->GetResolution();

		if (pointCount >= 2)
		{
			return false;
		}
		Mouse_x = e.x*resolution + ExGameGraphicInfo::GetGameGraphic()->GetBlackScreanSize().x;
		Mouse_y = e.y*resolution + ExGameGraphicInfo::GetGameGraphic()->GetBlackScreanSize().y;

		//minimum_x = x * resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().x;
		//	minimum_y = y * resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().y;

		total_x = getWidth() + x;//(/* minimum_x + */getWidth())*resolution  + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().x;
		total_y = getHeight() + y;//(/* minimum_y + */getHeight())*resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().y;

		minimum_x = x;
		minimum_y = y;

		if (minimum_x < Mouse_x && Mouse_x < total_x &&
			minimum_y < Mouse_y && Mouse_y < total_y)
		{
			return true;
		}

		bool ishorizen = false;

		//Todo :
		//해상도 바뀌면 바꿔야함 상수로 조정예정
		
		Point GameResolution(480, 800);

		Point TotalSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

		double Resolution = (float)TotalSize.x / (float)GameResolution.x;

		if (GameResolution.y * Resolution < TotalSize.y)
		{
			ishorizen = false;
		}
		else
		{
			ishorizen = true;
			Resolution = (float)TotalSize.y / (float)GameResolution.y;
		}

		int BlackScreanX = 0, BlackScreanY = 0;


		if (ishorizen)
		{
			BlackScreanX = (int)(TotalSize.x - (GameResolution.x * Resolution)) / 2;
		}
		else
		{
			BlackScreanY = (int)(TotalSize.y - (GameResolution.y * Resolution)) / 2;
		}


		return false;
	}


	//@Override
	void eventReceived(IUIBase* sender, ClickEventArgs e)
	{
	}

	//@Override
	Point getGridNum()
	{
		return m_gridNum;
	}

	//@Override
	void setGridNum(Point num)
	{

		m_gridNum = num;
	}

	//@Override
	UIVertical::Aligen_Vertical getAligenVertical()
	{

		return m_Aligen_Vertical;
	}

	//@Override
	void setAligenVertical(UIVertical::Aligen_Vertical value)
	{
		m_Aligen_Vertical = value;
	}

	//@Override
	UIHorizen::Aligen_Horizen getAligenHorizen()
	{
		return m_Aligen_Horizen;
	}

	//@Override
	void setAligenHorizen(UIHorizen::Aligen_Horizen value)
	{
		m_Aligen_Horizen = value;
	}

	//@Override
	Point getGridSize()
	{
		return m_gridSize;
	}

	//@Override
	void setGridSize(Point num)
	{
		m_gridSize = num;

	}


	//@Override
	void SetActualX(float _X) {
		isCaculated = true;
		_Acturalx = _X;
	}

	//@Override
	void SetActualY(float _Y) {
		isCaculated = true;
		_Acturaly = _Y;
	}

	//@Override
	float GetActualx() {
		if (isCaculated)
			return _Acturalx;
		else
			return x;
	}

	//@Override
	float GetActualy() {
		if (isCaculated)
			return _Acturaly;
		else
			return y;

	}


	Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration)
	{
		Animation* animation = (Animation*)new PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = AnimationType::LinearEaseIn;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		return (Animation*)animation;
	}

	Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, bool reverse)
	{
		Animation* animation = (Animation*)new PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = AnimationType::LinearEaseIn;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = reverse;
		return animation;
	}

	Animation* CreateAlphaAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new AlphaAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		return animation;
	}

	Animation* CreateAlphaAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* animation = (Animation*)new  AlphaAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mDelay = Delay;
		animation->mRepeat = false;
		return animation;
	}

	Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->Play();
		return animation;
	}

	Animation* CreateTranslateYAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionYAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->mDelay = Delay;
		animation->Play();
		return animation;
	}

	Animation* CreateTranslateXAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionXAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->Play();
		return animation;
	}

	Animation* CreateTranslateXAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* animation = (Animation*)new  PositionXAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		animation->mDelay = Delay;
		animation->Play();
		return animation;
	}

	Animation* CreateScaleXAnimation(float StartValue, float EndValue, long Duration)
	{
		Animation* _animation = (Animation*)new  ScaleXAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now();
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}

	Animation* CreateScaleXAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now();
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->m_AniType = ani;
		_animation->Play();
		return _animation;
	}

	Animation* CreateScaleXAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXAnimation();
		_animation->mDuration = Duration;
		_animation->mSaveStartTime = system_clock::now();
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->m_AniType = ani;
		_animation->mDelay = Delay;
		_animation->Play();
		return _animation;
	}

	Animation* CreateRotationAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* animation = (Animation*)new  RotationAnimation();
		animation->mDuration = Duration;
		animation->m_AniType = ani;
		animation->mSaveStartTime = system_clock::now();
		animation->mStartValue = StartValue;
		animation->mEndValue = EndValue;
		animation->mRepeat = false;
		return animation;
	}

	Animation* CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, bool mRepeat, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXYAnimation();
		_animation->mDuration = Duration;
		_animation->m_AniType = ani;
		_animation->mSaveStartTime = system_clock::now();
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = mRepeat;
		_animation->Play();
		return _animation;
	}


	Animation* CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXYAnimation();
		_animation->mDuration = Duration;
		_animation->m_AniType = ani;
		_animation->mSaveStartTime = system_clock::now();
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}

	Animation* CreateScaleXYAnimation(float StartValue, float EndValue, long Duration, long Delay, AnimationType ani)
	{
		Animation* _animation = (Animation*)new  ScaleXYAnimation();
		_animation->mDuration = Duration;
		_animation->m_AniType = ani;
		_animation->mSaveStartTime = system_clock::now();
		_animation->mStartValue = StartValue;
		_animation->mEndValue = EndValue;
		_animation->mDelay = Delay;
		_animation->mRepeat = false;
		_animation->Play();
		return _animation;
	}
	void OnDraw() {
		// TODO Auto-generated method stub



		if (vertexBuffer == NULL)
		{
			//Log.e("OnDraw", TextureName);
			return;
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glPushMatrix();

		// Telling OpenGL to enable textures.
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);

		// Tell OpenGL where our texture is located.
		glBindTexture(GL_TEXTURE_2D, KardNameFactory::GetKardNameFactory()->textureName[NowTextureId]);
		// Telling OpenGL where our UV coordinates are.
		glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);

		glFrontFace(GL_CW);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);


		float currentX = x;
		float currentY = y;

		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* _ani = (Animation*)*iter;
			
			if (_ani->mType ==  Type::TranslateX) {
				currentX = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
			}
			else if (_ani->mType ==  Type::TranslateY) {
				currentY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
			}
			else if (_ani->mType ==  Type::PositionX) {
				currentX = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				x = (int)currentX;

			}
			else if (_ani->mType ==  Type::PositionY) {
				currentY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				y = (int)currentY;
			}
			iter++;
		}


		glTranslatef(currentX, currentY, 0);


		float dw;
		float dh;

		dw = getWidth() / 2 /* + currentX*/;
		dh = getHeight() / 2 /* + currentY*/;

		iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* _ani = (Animation*)*iter;

			if (_ani->mType ==  Type::ScaleX) {
				float ScaleY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				//m.postScale(ScaleY, 1,dw,dh);
				glTranslatef(dw, dh, 0);
				glScalef(ScaleY, 1, 0);
				glTranslatef(dw *-1, dh *-1, 0);
				//m.postTranslate(x,y);
			}
			else if (_ani->mType ==  Type::ScaleY) {
				float ScaleY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				glTranslatef(dw, dh, 0);
				glScalef(1, ScaleY, 0);
				glTranslatef(dw *-1, dh *-1, 0);
			}
			else if (_ani->mType ==  Type::ScaleXY) {
				float ScaleXY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				glTranslatef(dw, dh, 0);
				glScalef(ScaleXY, ScaleXY, 0);
				glTranslatef(dw *-1, dh *-1, 0);
			}
			else if (_ani->mType ==  Type::Alpha) {
				float alpha = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				glColor4f(alpha / 255, alpha / 255, alpha / 255, alpha / 255);
			}
			else if (_ani->mType ==  Type::Rotate) {
				float rotate = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
				if (_ani->mDelay != 0)
					continue;
				glTranslatef(dw, dh, 0);
				glRotatef(rotate, 0, 0, 1);
				glTranslatef(dw *-1, dh *-1, 0);
			}
			iter++;
		}

		if (visiable == true)
			glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_SHORT, indexBuffer);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glPopMatrix();

		// Telling OpenGL to enable textures.
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void setbeckgroundImage(string string)
	{
		TextureName = string;
		
		AtlasObj* obj = KardNameFactory::GetKardNameFactory()->GetAtlasObj(string);

		if (obj == NULL)
		{
			///Log.e("setbeckgroundImage", string);
			return;
		}

		float vertices[] = {
			0.0f	, obj->Height	, 0.0f, // 0, Left Top
			obj->Width	, obj->Height	, 0.0f,	// 1, Right Top
			obj->Width	, 0.0f	, 0.0f,	// 2, Right Bottom
			0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
		};

		SetWidth(obj->Width);
		SetHeight(obj->Height);

		//Mapping coordinates for the vertices
		float texture[] = {
			obj->UV_X  , obj->UVB_Y ,
			obj->UVB_X , obj->UVB_Y ,
			obj->UVB_X , obj->UV_Y ,
			obj->UV_X  , obj->UV_Y ,
		};

		NowTextureId = obj->TextureNum;
	
		for (int i = 0; i < 8; i++)
			vertexBuffer[i] = vertices[i];

		for (int i = 0; i < 8; i++)
			textureBuffer[i] = texture[i];
	}

	void setbeckgroundImage(string string, float width, float height)
	{
		TextureName = string;
		AtlasObj* obj = KardNameFactory::GetKardNameFactory()->GetAtlasObj(string);

		if (obj == NULL)
		{
			//Log.e("setbeckgroundImage", string);
			return;
		}

		float vertices[] = {
			0.0f	, height, 0.0f, // 0, Left Top
			width	, height, 0.0f,	// 1, Right Top
			width	, 0.0f	, 0.0f,	// 2, Right Bottom
			0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
		};

		SetWidth(width);
		SetHeight(height);

		//Mapping coordinates for the vertices
		float texture[] = {
			obj->UV_X  , obj->UVB_Y ,
			obj->UVB_X , obj->UVB_Y ,
			obj->UVB_X , obj->UV_Y ,
			obj->UV_X  , obj->UV_Y ,
		};

		NowTextureId = obj->TextureNum;

		for (int i = 0; i < 8; i++)
			vertexBuffer[i] = vertices[i];

		for (int i = 0; i < 8; i++)
			textureBuffer[i] = texture[i];
	}

};
