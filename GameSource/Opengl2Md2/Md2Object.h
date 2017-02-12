#ifndef __MD2OBJECT_H__
#define __MD2OBJECT_H__
#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"

#include <vector>
#include <string>
#include <map>
#include <list>
#include "MarxObject.h"
#include "Texture.h"
#include "ModelInterface.h"
#include "Md2Model.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "AtlasObj.h"

#include "SelectableObject.h"
//#include "ImageControl.h"
using std::map;
using std::vector;
using std::string;
using namespace MarxEngine;

namespace MarxEngine {
	class ImageControl;
}
class Md2Object;



/////////////////////////////////////////////////////////////////////////////
//
// class Md2Object -- MD2 Object Class.
//
/////////////////////////////////////////////////////////////////////////////
class Md2Object :  public SelectableObject
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
	Md2Object (SelectableObject* _mother);
	Md2Object (SelectableObject* _mother, ModelInteface *model);
	Md2Object(SelectableObject* _mother, string ObjName);
	~Md2Object ();

public:
	// Public interface
	

	void drawObjectItp (bool animated, Md2RenderMode renderMode);
	void drawObjectFrame (int frame, Md2RenderMode renderMode);

	void SelectDraw();
	void animate (int startFrame, int endFrame, float percent);
	void animate (float percent);

	bool setModel (ModelInteface *model);
	bool setModel (const string &Modelname,const string &filename);
	//bool setModel (float Width,float Height, const string &textureName,const string &textureAlpha);
	bool setModel (float Width,float Height, string textureName,string textureAlpha, bool isAbsolute = false );
	string m_textureName;
	string m_textureAlpha;
	bool setModel (float Width,float Height, const string &textureName);
	void setScale (float scale) { _scale = scale; }
	float getScale () {return _scale; }
	void setAnim (const string &name);

	void SetAtlasObj(string ObjName);
	
	ImageControl* m_obj = NULL;

	bool NotSave = false;


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

	COMMONDATATYPE::Vector3d GetNowPostion();
	void SetNowPostion(COMMONDATATYPE::Vector3d pos);

	typedef std::shared_ptr<ModelInteface> Md2ModelSPtr;

	vec3_t &getRotate() {return m_rotation;}
	vec3_t &getTranslate() {return m_translate;}

	// Accessors
	ModelInteface *model () const { return _model.get(); }


	float scale () const { return _scale; }
	const string &currentAnim () const { return _currentAnim; }
	//void setRotate(float angle) { _model->setRotate(angle); }
	vec3_t m_rotation;
	vec3_t m_translate;

	/* // Child Object */
	void setNewPiece(Md2Object* obj);
	
	
	void Save(TiXmlElement * MapPieces);
	void Load(Md2Object* mother,TiXmlNode * MapPieces);

	void Refresh();

private:
	// Member variables
	Md2ModelSPtr _model;

	int _currFrame;
	int _nextFrame;
	float _interp;

	float _percent;
	float _scale;


	// Animation data
	const Md2Anim_t *_animInfo;
	string _currentAnim;
};
#endif