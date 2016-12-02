#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "ModelInterface.h"
#include <iostream>
#include <fstream>

#include "Md2Model.h"
#include "Md2Player.h"
#include "TextureManager.h"
#include "Md2Object.h"
#include "ProjectLoader.h"

using std::cout;
using std::cerr;
using std::endl;

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
	: _model (NULL), _currFrame (0), _nextFrame (0),
	_interp (0.0f), _percent (0.0f), _scale (1.0f), MarxObject(MARX_OBJECT_MD2_OBJECT)
{
	
}


Md2Object::Md2Object (ModelInteface *model)
	: _model (model), _currFrame (0), _nextFrame (0),
	_interp (0.0f), _percent (0.0f), _scale (1.0f), MarxObject(MARX_OBJECT_MD2_OBJECT)
{

	setModel (model);
}


// --------------------------------------------------------------------------
// Md2Object::~Md2Object
//
// Destructor.
// --------------------------------------------------------------------------

Md2Object::~Md2Object ()
{
}


// --------------------------------------------------------------------------
// Md2Object::drawObjectItp
//
// Draw the MD2 object with frame interpolation.
// --------------------------------------------------------------------------

void Md2Object::drawObjectItp (bool animated, Md2RenderMode renderMode)
{

	if(!_model.get())
		return;

	glPushName(_currentName);
	glPushMatrix ();

	// Axis rotation
	
	glTranslatef(m_translate[0],m_translate[1],m_translate[2]);

	glRotatef (-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef (-90.0f, 0.0f, 0.0f, 1.0f);

	

	glRotatef (m_rotation[0] , 1.0f, 0.0f, 0.0f);
	glRotatef (m_rotation[1] , 0.0f, 1.0f, 0.0f);
	glRotatef (m_rotation[2] , 0.0f, 0.0f, 1.0f);


	
	// Set model scale factor
	_model->setScale (_scale);

	glPushAttrib (GL_POLYGON_BIT);
	glFrontFace (GL_CW);

	//glScalef(_scale,_scale,_scale);

	//_model->renderSelectFrameImmediate();

	// Render the model
	switch (renderMode)
	{
	case kDrawImmediate:
		
		if(getSelect() == true)
			_model->renderSelectFrameImmediate();
		_model->drawModelItpImmediate (_currFrame, _nextFrame, _interp);
		
		break;

	case kDrawGLcmds:
		_model->drawModelItpWithGLcmds (_currFrame, _nextFrame, _interp);
		break;
	}

	

	// GL_POLYGON_BIT
	glPopAttrib ();
	
	glPopMatrix ();

	if (animated)
	{
		// Increase interpolation percent
		_interp += _percent;
	}

	
	glPopName();
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

	// Set model scale factor
	_model->setScale (_scale);

	glPushAttrib (GL_POLYGON_BIT);
	glFrontFace (GL_CW);


	// Render the model
	switch (renderMode)
	{
	case kDrawImmediate:

		if(getSelect() == true)
			_model->renderSelectFrameImmediate();
		_model->renderFrameImmediate (frame);
		
		break;

	case kDrawGLcmds:
		_model->renderFrameWithGLcmds (frame);
		break;
	}

	

	
	// GL_POLYGON_BIT
	glPopAttrib ();
	glPopMatrix ();

	glPopName();

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


void
	Md2Object::animate (float percent)
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

bool Md2Object::setModel (float Width,float Height, const string &textureName,const string &textureAlpha, bool isAbsolute)
{
	Md2ModelSPtr Model;
	Model = Md2ModelSPtr(new PieceModel (Width,Height));
	
	string TexturePath;
	if(isAbsolute == false )
	{
		TexturePath = ProjectLoader::getinstance().GetProjectPath() + "/" + textureName;
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
	

	string TexturePath = ProjectLoader::getinstance().GetProjectPath() + "/" + textureName;

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



