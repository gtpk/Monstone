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



void ImageControl::OnDraw(bool isSelect) {
	// TODO Auto-generated method stub

	if (NotExsistImage)
	{
		return;
	}
	
	if (vertexBuffer == NULL)
	{
		//Log.e("OnDraw", TextureName);
		return;
	}
	
	
	glDisable(GL_DEPTH_TEST);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();

	// Telling OpenGL to enable textures.

	
	
	
	//glBindTexture(GL_TEXTURE_2D, KardNameFactory::GetKardNameFactory()->textureName[NowTextureId]);
	// Telling OpenGL where our UV coordinates are.
	
		

	glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);
	TextureManager::Inst()->BindTexture(NowTextureId);


	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	// Tell OpenGL where our texture is located.
	

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


	glTranslatef(currentX, currentY, zindex);


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
			glTranslatef(dw, dh, zindex);
			glScalef(ScaleY, 1, 0);
			glTranslatef(dw *-1, dh *-1, zindex);
			//m.postTranslate(x,y);
		}
		else if (_ani->mType == Type::ScaleY) {
			float ScaleY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			glTranslatef(dw, dh, zindex);
			glScalef(1, ScaleY, 0);
			glTranslatef(dw *-1, dh *-1, zindex);
		}
		else if (_ani->mType == Type::ScaleXY) {
			float ScaleXY = _ani->getCurrentValue((system_clock::now() - _ani->mSaveStartTime).count());
			if (_ani->mDelay != 0)
				continue;
			glTranslatef(dw, dh, zindex);
			glScalef(ScaleXY, ScaleXY, 0);
			glTranslatef(dw *-1, dh *-1, zindex);
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
			glTranslatef(dw, dh, zindex);
			glRotatef(rotate, 0, 0, 1);
			glTranslatef(dw *-1, dh *-1, zindex);
		}
		iter++;
	}
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (visiable == true)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, index);
		
	if (isSelect)
	{
		glDisable(GL_TEXTURE_2D);

		glColor3f(1.0f, 0.0f, 1.0f);


		glBegin(GL_LINES);

		glLineWidth(10);

		float x1 = getWidth();
		float y1 = getHeight();
		float x2 = 0;
		float y2 = 0;

		glVertex2f(x1, y1);
		glVertex2f(x2, y1);

		glVertex2f(x2, y1);
		glVertex2f(x2, y2);

		glVertex2f(x2, y2);
		glVertex2f(x1, y2);

		glVertex2f(x1, y2);
		glVertex2f(x1, y1);

		glDisable(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnd();
		glEnable(GL_TEXTURE_2D);
	}

	glPopMatrix();


		

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glEnable(GL_DEPTH_TEST);
	// Telling OpenGL to enable textures.
	
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


void ImageControl::setbeckgroundImage(string string)
{
	NotExsistImage = false;
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

vector<ImageControl*> ImageControl::getAllChild()
{

	vector<ImageControl*> getAll_Child;

	//getAll_Child = new vector<ImageControl>();
	vector<ImageControl*>::iterator iter = m_Child.begin();
	while (iter != m_Child.end())
	{
		ImageControl* contator = (ImageControl*)*iter;
		getAll_Child.push_back(contator);
		ImageControl* _IContainer = dynamic_cast<ImageControl*>(contator);
		if (_IContainer != NULL)
		{
			vector<ImageControl*> coninside = _IContainer->getAllChild();
			vector<ImageControl*>::iterator iter2 = coninside.begin();
			while (iter2 != coninside.end())
			{
				getAll_Child.push_back((ImageControl*)*iter2);
				iter2++;
			}
			iter++;
		}
		else if (dynamic_cast<ImageControl*>(contator) != NULL)
		{
			getAll_Child.push_back((ImageControl*)contator);
		}
		else
		{
			iter++;
		}
	}
	

	return getAll_Child;
}

void ImageControl::Remove(ImageControl* child)
{
	vector<ImageControl*>::iterator iter = m_Child.begin();
	while (iter != m_Child.end())
	{
		ImageControl* contator = (ImageControl*)*iter;

		if (contator == child)
		{
			iter = m_Child.erase(iter);
			return;
		}
		iter++;
	}
}

bool ImageControl::AllAnimationFinished()
{

	vector<ImageControl*>::iterator iter = m_Child.begin();
	while (iter != m_Child.end())
	{
		ImageControl* GridControl = (ImageControl*)*iter;
		if (GridControl->AnimationisEnded() == false)
			return false;
	}

	return true;

}