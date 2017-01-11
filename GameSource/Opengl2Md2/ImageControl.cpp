#include "ImageControl.h"

ImageControl::ImageControl() : MarxObject(MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
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

ImageControl::ImageControl(string ObjName) : MarxObject(MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
{

	setbeckgroundImage(ObjName);

}

ImageControl::ImageControl(string ObjName, float width, float height) : MarxObject(MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
{

	setbeckgroundImage(ObjName, width, height);

}



void ImageControl::OnDraw() {
	// TODO Auto-generated method stub


	
	if (vertexBuffer == NULL)
	{
		//Log.e("OnDraw", TextureName);
		return;
	}
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_ALPHA_TEST);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();

	// Telling OpenGL to enable textures.

	
	
	
	//glBindTexture(GL_TEXTURE_2D, KardNameFactory::GetKardNameFactory()->textureName[NowTextureId]);
	// Telling OpenGL where our UV coordinates are.
	

	
	
	glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);

	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	// Tell OpenGL where our texture is located.
	TextureManager::Inst()->BindTexture(NowTextureId);

	float currentX = x;
	float currentY = y;

	vector<Animation*>::iterator iter = animations.begin();
	while (iter != animations.end())
	{
		Animation* _ani = (Animation*)*iter;

		if (_ani->mType == Type::TranslateX) {
			currentX = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
		}
		else if (_ani->mType == Type::TranslateY) {
			currentY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
		}
		else if (_ani->mType == Type::PositionX) {
			currentX = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			x = (int)currentX;

		}
		else if (_ani->mType == Type::PositionY) {
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

		if (_ani->mType == Type::ScaleX) {
			float ScaleY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			//m.postScale(ScaleY, 1,dw,dh);
			glTranslatef(dw, dh, 0);
			glScalef(ScaleY, 1, 0);
			glTranslatef(dw *-1, dh *-1, 0);
			//m.postTranslate(x,y);
		}
		else if (_ani->mType == Type::ScaleY) {
			float ScaleY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			glTranslatef(dw, dh, 0);
			glScalef(1, ScaleY, 0);
			glTranslatef(dw *-1, dh *-1, 0);
		}
		else if (_ani->mType == Type::ScaleXY) {
			float ScaleXY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			glTranslatef(dw, dh, 0);
			glScalef(ScaleXY, ScaleXY, 0);
			glTranslatef(dw *-1, dh *-1, 0);
		}
		else if (_ani->mType == Type::Alpha) {
			float alpha = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			glColor4f(alpha / 255, alpha / 255, alpha / 255, alpha / 255);
		}
		else if (_ani->mType == Type::Rotate) {
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
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, index);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	

	// Telling OpenGL to enable textures.
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void ImageControl::setbeckgroundImage(string string)
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

	for (int i = 0; i < 12; i++)
		vertexBuffer[i] = vertices[i];

	for (int i = 0; i < 8; i++)
		textureBuffer[i] = texture[i];
}

void ImageControl::setbeckgroundImage(string string, float width, float height)
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

	for (int i = 0; i < 12; i++)
		vertexBuffer[i] = vertices[i];

	for (int i = 0; i < 8; i++)
		textureBuffer[i] = texture[i];
}