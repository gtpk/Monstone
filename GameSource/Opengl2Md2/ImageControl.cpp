#include "ImageControl.h"
#include "ObjectNumberingMananger.h"
#include "KardNameFactory.h"
#include "TextureManager.h"
#include "ExGameGraphicInfo.h"
#include "Atlasobj.h"

using namespace MarxEngine;
namespace MarxEngine
{
	ImageControl::ImageControl() : MarxObject(MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
	{
		m_Aligen_Vertical = UIVertical::Aligen_Vertical::defalt;
		m_Aligen_Horizen = UIHorizen::Aligen_Horizen::defalt;

		m_gridNum = Point(0, 0);
		ScaleX = 1;
		ScaleY = 1;
		
		isNotClickable = false;
		isWidthPercent = true;
		isHeightPercent = true;
		_Acturalx = 0;
		_Acturaly = 0;
		isCaculated = false;
		_currentName = ObjectNumberingMananger::getInstance()->getNumber();
	}

	ImageControl::ImageControl(string ObjName) : MarxObject(MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
	{
		ImageControl();
		setbeckgroundImage(ObjName);
		_currentName = ObjectNumberingMananger::getInstance()->getNumber();
	}

	ImageControl::ImageControl(string ObjName, float width, float height) : MarxObject(MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
	{
		ImageControl();
		//
		setbeckgroundImage(ObjName, width, height);
		_currentName = ObjectNumberingMananger::getInstance()->getNumber();
	}

	ImageControl::~ImageControl()
	{
		if (MarxWorld::getInstance().Volkes != NULL)
		{
			MarxWorld::getInstance().Volkes->DeleteImageControl(this);
		}
		
	}

	//@Override
	void ImageControl::SetWidth(float width)
	{
		m_Size.x = (int)width;

		float vertices[] = {
			0.0f	, m_Size.y	, 0.0f, // 0, Left Top
			m_Size.x	, m_Size.y	, 0.0f,	// 1, Right Top
			m_Size.x	, 0.0f	, 0.0f,	// 2, Right Bottom
			0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
		};

		for (int i = 0; i < 12; i++)
			vertexBuffer[i] = vertices[i];
	}

	//@Override
	void ImageControl::SetHeight(float height)
	{

		if (m_Size.y == height)
			return;

		if (m_Size.x == 0)
			m_Size.x = getWidth();

		m_Size.y = (int)height;

		float vertices[] = {
			0.0f	, m_Size.y	, 0.0f, // 0, Left Top
			m_Size.x	, m_Size.y	, 0.0f,	// 1, Right Top
			m_Size.x	, 0.0f	, 0.0f,	// 2, Right Bottom
			0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
		};

		for (int i = 0; i < 12; i++)
			vertexBuffer[i] = vertices[i];
	}



	void ImageControl::OnDraw(bool isSelect) {
		// TODO Auto-generated method stub

		if (NotExsistImage)
		{
			vector<ImageControl*> m_Child = getAllChild();
			vector<ImageControl*>::iterator itor = m_Child.begin();

			while (itor != m_Child.end())
			{
				ImageControl* node = *itor;
				node->OnDraw(isSelect);
				itor++;
			}
			return;
		}

		if (vertexBuffer == NULL)
		{
			//Log.e("OnDraw", TextureName);
			return;
		}

		if(_currentName != -1)
			glPushName(_currentName);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE); //뒷면 보이게 하는것
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glPushMatrix();

		// Telling OpenGL to enable textures.




		//glBindTexture(GL_TEXTURE_2D, KardNameFactory::GetKardNameFactory()->textureName[NowTextureId]);
		// Telling OpenGL where our UV coordinates are.



		glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);
		TextureManager::Inst()->BindTexture(NowTextureId);
		glColor4f(transparent / 255, transparent / 255, transparent / 255, transparent / 255);

		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		// Tell OpenGL where our texture is located.


		float currentX = x;
		float currentY = y;

		vector<Animation*>::iterator iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* _ani = (Animation*)*iter;

			if (_ani->mType == MARXAnimatnionType::TranslateX) {
				currentX = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
			}
			else if (_ani->mType == MARXAnimatnionType::TranslateY) {
				currentY = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
			}
			else if (_ani->mType == MARXAnimatnionType::PositionX) {
				currentX = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				x = (int)currentX;

			}
			else if (_ani->mType == MARXAnimatnionType::PositionY) {
				currentY = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				y = (int)currentY;
			}
			iter++;
		}


		float dw = getWidth() / 2 /* + currentX*/;
		float dh = getHeight() / 2 /* + currentY*/;

		
		glTranslatef(currentX, currentY, zindex);
		//glScalef(ScaleX, ScaleY, 0);
		glRotatef(m_rotate, 0, 0, 1);

		glTranslatef(dw, dh, zindex);
		glScalef(ScaleX, ScaleY, 1);
		glTranslatef(dw *-1, dh *-1, zindex);


		
		iter = animations.begin();
		while (iter != animations.end())
		{
			Animation* _ani = (Animation*)*iter;

			if (_ani->mType == MARXAnimatnionType::ScaleX) {
				float ScaleY = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				//m.postScale(ScaleY, 1,dw,dh);
				glTranslatef(dw, dh, zindex);
				glScalef(ScaleY, 1, 0);
				glTranslatef(dw *-1, dh *-1, zindex);
				//m.postTranslate(x,y);
			}
			else if (_ani->mType == MARXAnimatnionType::ScaleY) {
				float ScaleY = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				glTranslatef(dw, dh, zindex);
				glScalef(1, ScaleY, 0);
				glTranslatef(dw *-1, dh *-1, zindex);
			}
			else if (_ani->mType == MARXAnimatnionType::ScaleXY) {
				float ScaleXY = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				glTranslatef(dw, dh, zindex);
				glScalef(ScaleXY, ScaleXY, 0);
				glTranslatef(dw *-1, dh *-1, zindex);
			}
			else if (_ani->mType == MARXAnimatnionType::Alpha) {
				float alpha = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				glColor4f(alpha / 255, alpha / 255, alpha / 255, alpha / 255);
			}
			else if (_ani->mType == MARXAnimatnionType::Rotate) {
				float rotate = _ani->getCurrentValue(system_clock::now().time_since_epoch().count() / 100000 - _ani->mSaveStartTime);
				if (_ani->mDelay != 0)
				{
					iter++;
					continue;
				}
				glTranslatef(dw, dh, zindex);
				glRotatef(m_rotate + rotate, 0, 0, 1);
				glTranslatef(dw *-1, dh *-1, zindex);
			}
			iter++;
		}
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (visiable == true)
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, index);

		if (_currentName != -1)
			glPopName();

		if (isSelect || m_isSelect)
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

		

		{
			//vector<ImageControl*> m_Child = this->m_Child;
			vector<ImageControl*>::iterator itor = m_Child.begin();

			while (itor != m_Child.end())
			{
				ImageControl* node = *itor;
				node->OnDraw(isSelect);
				itor++;
			}
		}


		glPopMatrix();




		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glEnable(GL_DEPTH_TEST);
		// Telling OpenGL to enable textures.

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);



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
			if (contator != NULL)
			{
				vector<ImageControl*> coninside = contator->getAllChild();
				vector<ImageControl*>::iterator iter2 = coninside.begin();
				while (iter2 != coninside.end())
				{
					getAll_Child.push_back((ImageControl*)*iter2);
					iter2++;
				}
				iter++;
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
				delete contator;
				iter = m_Child.erase(iter);
				return;
			}
			iter++;
		}
	}

	void ImageControl::deleteSelectPiece(int tempname)
	{
		vector<ImageControl*>::iterator iter = m_Child.begin();
		while (iter != m_Child.end())
		{
			ImageControl* contator = (ImageControl*)*iter;

			if (contator->_currentName == tempname)
			{
				delete contator;
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


	void ImageControl::Load(ImageControl* mother, TiXmlNode * MapPieces)
	{
		TiXmlNode * ChildNode = MapPieces->FirstChild("Child");
		if (ChildNode == NULL)
			return;
		TiXmlNode * Piece = ChildNode->FirstChild("ImageControl");
		for (; Piece != NULL; Piece = Piece->NextSibling())
		{

			TiXmlElement* pelement = Piece->ToElement();

			const char* _Name = pelement->Attribute("Name");
			const char* _TextureName = pelement->Attribute("TextureName");
			int _transparent = 255;
			pelement->Attribute("transparent", &_transparent);
			float _ScaleX;
			pelement->QueryFloatAttribute("ScaleX", &_ScaleX);
			float _ScaleY;
			pelement->QueryFloatAttribute("ScaleY", &_ScaleY);
			float _x;
			pelement->QueryFloatAttribute("x", &_x);
			float _y;
			pelement->QueryFloatAttribute("y", &_y);
			float _zindex;
			pelement->QueryFloatAttribute("zindex", &_zindex);
			float _m_rotate;
			pelement->QueryFloatAttribute("m_rotate", &_m_rotate);
			float Width;
			pelement->QueryFloatAttribute("Width", &Width);
			float Height;
			pelement->QueryFloatAttribute("Height", &Height);

			ImageControl* child = ImageControl::CreateImageControl(mother, string(_TextureName), _Name, _x, _y, Width, Height);
			child->zindex = _zindex;
			child->m_rotate = _m_rotate;
			child->ScaleX = _ScaleX;
			child->ScaleY = _ScaleY;
			child->Load(child, pelement);
		}
	}

	void ImageControl::Save(TiXmlElement * MapPieces)
	{
		TiXmlElement * Piece;
		Piece = new TiXmlElement("ImageControl");
		MapPieces->LinkEndChild(Piece);
		Piece->SetAttribute("Name", Name.c_str());
		Piece->SetAttribute("TextureName", TextureName.c_str());
		Piece->SetAttribute("transparent", transparent);
		Piece->SetDoubleAttribute("ScaleX", ScaleX);
		Piece->SetDoubleAttribute("ScaleY", ScaleY);
		Piece->SetDoubleAttribute("x", x);
		Piece->SetDoubleAttribute("y", y);
		Piece->SetDoubleAttribute("zindex", zindex);
		Piece->SetDoubleAttribute("m_rotate", m_rotate);
		Piece->SetDoubleAttribute("Width", m_Size.x);
		Piece->SetDoubleAttribute("Height", m_Size.y);

		TiXmlElement * Child;
		Child = new TiXmlElement("Child");
		Piece->LinkEndChild(Child);
		{
			std::vector<ImageControl*>::iterator _iter = m_Child.begin();
			while (_iter != m_Child.end())
			{
				ImageControl* var = *_iter;
				var->Save(Child);
				_iter++;
			}
		}

		//std::list<Md2Object*>::iterator _iter = child.begin();
		//while (_iter != child.end())
		//{
		//	Md2Object* var = *_iter;
		//	if (var->GetUniqNumber() == number)
		//		return var;
		//	var = var->setSelectObj(number);
		//	if (var != NULL)
		//		return  var;
		//	_iter++;
		//}
	}
}