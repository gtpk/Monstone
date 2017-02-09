#pragma once
#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "ModelInterface.h"
#include <iostream>
#include <fstream>

#include "Md2Model.h"
#include "MarxWorld.h"
#include "TextureManager.h"
#include "Md2Object.h"
#include "ProjectLoader.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "ImageControl.h"
#include "ObjectNumberingMananger.h"
using std::cout;
using std::cerr;
using std::endl;
using namespace MarxEngine;
/////////////////////////////////////////////////////////////////////////////
//
// class Md2Object implementation.
//
/////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------------
// Md2Object::Md2Object
//
// Constructors.
// --------------------------------------------------------------------------

Md2Object::Md2Object ()
	: _model (NULL), _currFrame (0), _nextFrame (0), m_obj(NULL),
	_interp (0.0f), _percent (0.0f), _scale (1.0f)
{
	
}


Md2Object::Md2Object (ModelInteface *model)
	: _model (model), _currFrame (0), _nextFrame (0), m_obj(NULL),
	_interp (0.0f), _percent (0.0f), _scale (1.0f)
{

	setModel (model);
}

Md2Object::Md2Object(string ObjName)
	: _model(NULL), _currFrame(0), _nextFrame(0), m_obj(NULL),
	_interp(0.0f), _percent(0.0f), _scale(1.0f)
{
	SetAtlasObj(ObjName);
}

// --------------------------------------------------------------------------
// Md2Object::~Md2Object
//
// Destructor.
// --------------------------------------------------------------------------

Md2Object::~Md2Object ()
{
	
	
}

//_NextID


void Md2Object::SetAtlasObj(string ObjName)
{
	m_obj = new ImageControl(ObjName);

	ObjectNumberingMananger::getInstance()->UnUseNumber(m_obj->_currentName,this);
	m_obj->_currentName = _currentName;
}


void Md2Object::Refresh()
{
	std::list<SelectableObject*>::iterator md2begin = child.begin();
	std::list<SelectableObject*>::iterator md2End = child.end();
	for (; md2begin != md2End; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		MarxWorld::getInstance().Volkes->setNewPiece(this,node);
		md2begin++;
	}

	
}



// --------------------------------------------------------------------------
// Md2Object::drawObjectItp
//
// Draw the MD2 object with frame interpolation.
// --------------------------------------------------------------------------
void Md2Object::SelectDraw()
{
	//glPushName(_currentName);
	glPushMatrix();

	glTranslatef(m_translate[0], m_translate[1], m_translate[2]);

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(m_rotation[0], 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotation[2], 0.0f, 0.0f, 1.0f);

	if (m_obj != NULL)
	{
		m_obj->_currentName = _currentName;
		m_obj->zindex = m_translate[2];
		m_obj->OnDraw(getSelect());
	}
	else if (_model.get())
	{
		_model->setScale(_scale);
		glPushAttrib(GL_POLYGON_BIT);
		glFrontFace(GL_CW);
		SelectNumbers[8] = _currentName;
		if (getSelect() == true)
			_model->renderSelectFrameImmediate(SelectNumbers);
		glPopAttrib();
	}

	glPopName();

	std::list<SelectableObject*>::iterator _iter = child.begin();
	while (_iter != child.end())
	{
		Md2Object* var =(Md2Object*)*_iter;
		var->SelectDraw();
		_iter++;
	}
	glPopMatrix();
}



void Md2Object::drawObjectItp (bool animated, Md2RenderMode renderMode)
{


	glPushName(_currentName);
	glPushMatrix();

	// Axis rotation

	glTranslatef(m_translate[0], m_translate[1], m_translate[2]);

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);



	glRotatef(m_rotation[0], 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotation[2], 0.0f, 0.0f, 1.0f);

	if (m_obj != NULL)
	{
		m_obj->_currentName = _currentName;
		m_obj->zindex = m_translate[2];
		m_obj->OnDraw(getSelect());
	}
	else if (_model.get())
	{
		// Set model scale factor
		_model->setScale(_scale);


		glPushAttrib(GL_POLYGON_BIT);
		glFrontFace(GL_CW);

		switch (renderMode)
		{
		case kDrawImmediate:
			_model->drawModelItpImmediate(_currFrame, _nextFrame, _interp);
			break;

		case kDrawGLcmds:
			_model->drawModelItpWithGLcmds(_currFrame, _nextFrame, _interp);
			break;
		}
		glPopAttrib();
	}
	
	glPopName();

	std::list<SelectableObject*>::iterator _iter = child.begin();
	while (_iter != child.end())
	{
		Md2Object* var = (Md2Object*)*_iter;
		var->drawObjectItp(animated, renderMode);
		_iter++;
	}
	// GL_POLYGON_BIT
	//glPopAttrib();

	glPopMatrix();

}




// --------------------------------------------------------------------------
// Md2Object::drawObjectFrame
//
// Draw the MD2 object for the specified frame.
// --------------------------------------------------------------------------

void Md2Object::drawObjectFrame (int frame, Md2RenderMode renderMode)
{
	glPushName(_currentName);
	glPushMatrix ();

	glTranslatef(m_translate[0],m_translate[1],m_translate[2]);

	// Axis rotation
	glRotatef (-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef (-90.0f, 0.0f, 0.0f, 1.0f);

	
	glRotatef (m_rotation[0] , 1.0f, 0.0f, 0.0f);
	glRotatef (m_rotation[1] , 0.0f, 1.0f, 0.0f);
	glRotatef (m_rotation[2] , 0.0f, 0.0f, 1.0f);


	glPushAttrib (GL_POLYGON_BIT);
	glFrontFace (GL_CW);

	if (m_obj == NULL)
	{

		// Set model scale factor
		_model->setScale(_scale);
		// Render the model
		switch (renderMode)
		{
		case kDrawImmediate:
			_model->renderFrameImmediate (frame);
		
			break;

		case kDrawGLcmds:
			_model->renderFrameWithGLcmds (frame);
			break;
		}
	}
	else
	{
		m_obj->_currentName = _currentName;
		m_obj->OnDraw();
	}



	
	// GL_POLYGON_BIT
	

	glPopName();
	std::list<SelectableObject*>::iterator _iter = child.begin();
	while (_iter != child.end())
	{
		Md2Object* var = (Md2Object*)*_iter;
		var->drawObjectFrame(frame, renderMode);
		_iter++;
	}
	glPopAttrib();
	glPopMatrix();

	//_model->renderSelectFrameImmediate();

}


// --------------------------------------------------------------------------
// Md2Object::Animate
//
// Animate the object.  Compute current and next frames, and the
// interpolation percent.
// --------------------------------------------------------------------------

void
	Md2Object::animate (int startFrame, int endFrame, float percent)
{
	// _currFrame must range between startFrame and endFrame
	if (_currFrame < startFrame)
		_currFrame = startFrame;

	if (_currFrame > endFrame)
		_currFrame = startFrame;

	_percent = percent;

	// Compute current and next frames.
	if (_interp >= 1.0)
	{
		_interp = 0.0f;
		_currFrame++;

		if (_currFrame >= endFrame)
			_currFrame = startFrame;

		_nextFrame = _currFrame + 1;

		if (_nextFrame >= endFrame)
			_nextFrame = startFrame;
	}
}


void Md2Object::animate (float percent)
{
	// Use the current animation
	animate (_animInfo->start, _animInfo->end, percent);
}


// --------------------------------------------------------------------------
// Md2Object::setModel
//
// Attach mesh model to object.
// --------------------------------------------------------------------------

bool Md2Object::setModel (ModelInteface *model)
{
	
	_model = Md2ModelSPtr(model);

	if (_model)
	{
		// Set first animation as default animation
		if( _model->anims().empty() == false )
		{
			_animInfo = &_model->anims ().begin ()->second;
			_currentAnim = _model->anims ().begin ()->first;
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool Md2Object::setModel (const string &Modelname,const string &filename)
{
	Md2ModelSPtr Model;
	// 메시 불러오기
	Model = Md2ModelSPtr(new Md2Model (Modelname));


	// 텍스쳐 불러오기
	if(Model->setTexture(filename) == false)
	{
		Model->loadTexture(filename);
		Model->setTexture (filename);
	}		
	
	if(!Model.get())
		return false;

	// Set first animation as default animation

	_model = Model;
	
	if( _model->anims().empty() == false )
	{
		_animInfo = &_model->anims ().begin ()->second;
		_currentAnim = _model->anims ().begin ()->first;
	}
}
// --------------------------------------------------------------------------
// Md2Object::setModel
//
// Attach mesh model to object.
// --------------------------------------------------------------------------

bool Md2Object::setModel (float Width,float Height, string textureName,
	string textureAlpha, bool isAbsolute)
{
	Md2ModelSPtr Model;
	Model = Md2ModelSPtr(new PieceModel (Width,Height));
	m_textureName = textureName.c_str();
	m_textureAlpha =  textureAlpha.c_str();
	string TexturePath;
	if(isAbsolute == false )
	{
		TexturePath = ProjectLoader::getinstance()->GetProjectPath() + "/" + textureName;
	}
	else
	{
		TexturePath = textureName;
	}
	

	if(Model->setTexture (textureName,textureAlpha) == false)
	{
		Model->loadTexture(textureName,textureAlpha);
		Model->setTexture (textureName,textureAlpha);
	}

	if(!Model.get())
		return false;

	_model = Model;

	// Set first animation as default animation
	if( _model->anims().empty() == false )
	{
		_animInfo = &_model->anims ().begin ()->second;
		_currentAnim = _model->anims ().begin ()->first;
	}
	else
	{
		return false;
	}

	return true;
}


bool Md2Object::setModel (float Width,float Height, const string &textureName)
{
	Md2ModelSPtr Model;
	Model = Md2ModelSPtr(new PieceModel (Width,Height));
	

	string TexturePath = ProjectLoader::getinstance()->GetProjectPath() + "/" + textureName;

	if(Model->setTexture (textureName) == false)
	{
		Model->loadTexture(textureName);
		Model->setTexture (textureName);
	}

	if(!Model.get())
		return false;

	_model = Model;

	// Set first animation as default animation
	if( _model->anims().empty() == false )
	{
		_animInfo = &_model->anims ().begin ()->second;
		_currentAnim = _model->anims ().begin ()->first;
	}
	else
	{
		return false;
	}

	return true;
}

void Md2Object::setNewPiece(Md2Object* obj)
{
	if (obj == this)
	{
		printf("ERROR!! Self Insert!\n");
		return;
	}
	child.push_back(obj);
}

void Md2Object::Load(Md2Object* mother,TiXmlNode * MapPieces)
{
	TiXmlNode * ChildNode = MapPieces->FirstChild("Child");
	if (ChildNode == NULL)
		return;
	TiXmlNode * Piece = ChildNode->FirstChild("Piece");
	for (; Piece != NULL; Piece = Piece->NextSibling())
	{
		int name = 101;
		MARXOBJECT_TYP_ENUM type;
		float Scale = 0.1;
		float width;
		float height;

		TiXmlElement* pelement = Piece->ToElement();

		pelement->Attribute("Name", &name);
		const char* TextureName = pelement->Attribute("TextureName");
		const char* AlphaTexture = pelement->Attribute("AlphaTexture");
		const char* Md2Name = pelement->Attribute("ModelName");
		int i_type = 0;
		pelement->Attribute("MARXOBJECT_TYP_ENUM", &i_type);
		type = (MARXOBJECT_TYP_ENUM)i_type;
		pelement->QueryFloatAttribute("Scale", &Scale);
		pelement->QueryFloatAttribute("Width", &width);
		pelement->QueryFloatAttribute("Height", &height);

		vec3_t m_translate;

		//TiXmlNode* Trancerate = Piece->FirstChild("Trancerate");
		//TiXmlElement* pTracerate = Trancerate->ToElement();
		pelement->QueryFloatAttribute("Tranceratex", &m_translate[0]);
		pelement->QueryFloatAttribute("Tranceratey", &m_translate[1]);
		pelement->QueryFloatAttribute("Tranceratez", &m_translate[2]);

		vec3_t m_rotation;
		//TiXmlNode* Rotation = Piece->FirstChild("Rotation");
		//TiXmlElement* pRotation = Rotation->ToElement();
		pelement->QueryFloatAttribute("Rotationx", &m_rotation[0]);
		pelement->QueryFloatAttribute("Rotationy", &m_rotation[1]);
		pelement->QueryFloatAttribute("Rotationz", &m_rotation[2]);

		if (type == MARXOBJECT_TYP_ENUM::MARX_OBJECT_MD2_MODEL)
		{
			std::ifstream pieceifs;

			string path = Md2Name;
			pieceifs.open(path.c_str(), std::ios::binary);

			if (pieceifs.fail())
			{
				pieceifs.close();
				continue;
			}
			GLfloat pos = -10;

			Md2Object* obj = new Md2Object();
			//_WorldPiece.push_back()
			obj->setName(name);
			obj->setModel(path, TextureName);
			obj->setRotate(m_rotation[0], m_rotation[1], m_rotation[2]);
			obj->setTranslate(m_translate[0], m_translate[1], m_translate[2]);
			obj->setScale(Scale);
			child.push_back(obj);
		}
		else if (type == MARXOBJECT_TYP_ENUM::MARX_OBJECT_MD2_OBJECT)
		{
			string TextureName_str = TextureName;
			TextureName_str = TextureName_str.substr(
				string(MarxWorld::getInstance()._RootDirctory + "\\asset\\").length(), TextureName_str.length());
			string AlphaTexture_str = AlphaTexture;
			AlphaTexture_str = AlphaTexture_str.substr(
				string(MarxWorld::getInstance()._RootDirctory + "\\asset\\").length(), AlphaTexture_str.length());

			Md2Object* obj = MarxWorld::getInstance().setNewPiece(mother,width, height, TextureName_str.c_str(), AlphaTexture_str.c_str());
			obj->setName(name);
			obj->setRotate(m_rotation[0], m_rotation[1], m_rotation[2]);
			obj->setTranslate(m_translate[0], m_translate[1], m_translate[2]);
			obj->setScale(Scale);
			obj->Load(obj,Piece);
		}
	}
}

void Md2Object::Save(TiXmlElement * MapPieces)
{
	TiXmlElement * Piece;
	Piece = new TiXmlElement("Piece");
	MapPieces->LinkEndChild(Piece);
	Piece->SetAttribute("Name", this->GetUniqNumber());
	Piece->SetAttribute("TextureName", this->model()->getTextureName().c_str());
	Piece->SetAttribute("AlphaTexture", this->model()->getAlphaTextureName().c_str());
	Piece->SetAttribute("ModelName", this->model()->getMd2name().c_str());
	Piece->SetAttribute("MARXOBJECT_TYP_ENUM", this->GetType());
	Piece->SetDoubleAttribute("Scale", this->scale());

	Piece->SetDoubleAttribute("Tranceratex", this->m_translate[0]);
	Piece->SetDoubleAttribute("Tranceratey", this->m_translate[1]);
	Piece->SetDoubleAttribute("Tranceratez", this->m_translate[2]);

	Piece->SetDoubleAttribute("Rotationx", this->m_rotation[0]);
	Piece->SetDoubleAttribute("Rotationy", this->m_rotation[1]);
	Piece->SetDoubleAttribute("Rotationz", this->m_rotation[2]);

	Piece->SetDoubleAttribute("Width", this->_model->m_Width);
	Piece->SetDoubleAttribute("Height", this->_model->m_Height);

	TiXmlElement * Child;
	Child = new TiXmlElement("Child");
	Piece->LinkEndChild(Child);
	{
		std::list<SelectableObject*>::iterator _iter = child.begin();
		while (_iter != child.end())
		{
			Md2Object* var = (Md2Object*)*_iter;
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

// --------------------------------------------------------------------------
// Md2Object::setAnim
//
// Set current object animation.
// --------------------------------------------------------------------------

void Md2Object::setAnim (const string &name)
{
	// Try to find the desired animation
	ModelInteface::AnimMap::const_iterator itor;
	itor = _model->anims ().find (name);

	if (itor != _model->anims ().end ())
	{
		_animInfo = &itor->second;
		_currentAnim = name;
	}

}


void Md2Object::setRotate(vec3_t angle ) 
{
	m_rotation[0] += angle[0]; 
	m_rotation[1] += angle[1]; 
	m_rotation[2] = angle[2]; 
}

void Md2Object::setRotate(GLfloat x,GLfloat y,GLfloat z ) 
{
	m_rotation[0] = x; 
	m_rotation[1] = y; 
	m_rotation[2] = z; 
}

int Md2Object::setRotate_Lua(GLfloat x,GLfloat y,GLfloat z ) 
{
	m_rotation[0] = x; 
	m_rotation[1] = y; 
	m_rotation[2] = z; 
	return 0;
}

void Md2Object::setTranslate(vec3_t trance ) 
{
	m_translate[0] = trance[0]; 
	m_translate[1] = trance[1]; 
	m_translate[2] = trance[2]; 
}

void Md2Object::setTranslate(GLfloat x,GLfloat y,GLfloat z ) 
{
	m_translate[0] = x; 
	m_translate[1] = y; 
	m_translate[2] = z; 
}

int Md2Object::setTranslate_Lua(GLfloat x,GLfloat y,GLfloat z ) 
{
	m_translate[0] += x; 
	m_translate[1] += y; 
	m_translate[2] += z; 
	return 0;
}



