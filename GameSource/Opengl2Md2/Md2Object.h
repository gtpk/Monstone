#ifndef __MD2OBJECT_H__
#define __MD2OBJECT_H__
#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"

#include <gl/gl.h>
// glu.h for gluViewport
#include <gl/glu.h>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "MarxObject.h"
#include "Texture.h"
#include "ModelInterface.h"
#include "Md2Model.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
using std::map;
using std::vector;
using std::string;

/////////////////////////////////////////////////////////////////////////////
//
// class Md2Object -- MD2 Object Class.
//
/////////////////////////////////////////////////////////////////////////////



class Md2Object : public MarxObject
{
public:
	// Public internal types/enums
	enum Md2RenderMode
	{
		kDrawImmediate = 0,
		kDrawGLcmds,
	};

	

public:
	// Constructor/destructor
	Md2Object ();
	Md2Object (ModelInteface *model);
	~Md2Object ();

public:
	// Public interface
	void drawObjectItp (bool animated, Md2RenderMode renderMode);
	void drawObjectFrame (int frame, Md2RenderMode renderMode);
	void animate (int startFrame, int endFrame, float percent);
	void animate (float percent);

	bool setModel (ModelInteface *model);
	bool setModel (const string &Modelname,const string &filename);
	//bool setModel (float Width,float Height, const string &textureName,const string &textureAlpha);
	bool setModel (float Width,float Height, const string &textureName,const string &textureAlpha, bool isAbsolute = false );
	bool setModel (float Width,float Height, const string &textureName);
	void setScale (float scale) { _scale = scale; }
	float getScale () {return _scale; }
	void setAnim (const string &name);

	void setName(GLint name);

	int GetUniqNumber() { return _currentName; }

	void setRotate(vec3_t angle );

	void setRotate(GLfloat x,GLfloat y,GLfloat z );

	int setRotate_Lua(GLfloat x,GLfloat y,GLfloat z );

	GLfloat getRotateX_Lua()
	{
		return m_rotation[0];
	}

	GLfloat getRotateY_Lua()
	{
		return m_rotation[1];
	}

	GLfloat getRotateZ_Lua()
	{
		return m_rotation[2];
	}

	void setTranslate(vec3_t trance );

	void setTranslate(GLfloat x,GLfloat y,GLfloat z );

	int setTranslate_Lua(GLfloat x,GLfloat y,GLfloat z );

	GLfloat getTranslateX_Lua()
	{
		return m_translate[0];
	}

	GLfloat getTranslateY_Lua()
	{
		return m_translate[1];
	}

	GLfloat getTranslateZ_Lua()
	{
		return m_translate[2];
	}



	typedef std::shared_ptr<ModelInteface> Md2ModelSPtr;

	vec3_t &getRotate() {return m_rotation;}
	vec3_t &getTranslate() {return m_translate;}

	// Accessors
	ModelInteface *model () const { return _model.get(); }

	void setSelect (bool select){m_bselect = select;}
	bool getSelect (){ return m_bselect;}

	
	bool m_bselect;

	float scale () const { return _scale; }
	const string &currentAnim () const { return _currentAnim; }
	//void setRotate(float angle) { _model->setRotate(angle); }
	vec3_t m_rotation;
	vec3_t m_translate;

	/* // Child Object */
	void setNewPiece(Md2Object* obj);

	Md2Object* setSelectObj(int number);

	void Save(TiXmlElement * MapPieces);
	void Load(Md2Object* mother,TiXmlNode * MapPieces);
private:
	std::list<Md2Object*> child;

	

private:
	// Member variables
	Md2ModelSPtr _model;

	int _currFrame;
	int _nextFrame;
	float _interp;

	float _percent;
	float _scale;
	// 번호 이름은 절대 외부 접근 금지
	int _currentName;

	// Animation data
	const Md2Anim_t *_animInfo;
	string _currentAnim;
};
#endif