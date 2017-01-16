#ifndef __MD2INTERFACE_H__
#define __MD2INTERFACE_H__


#include "Texture.h"
#include <string>

using std::string;



// Animation infos
struct Md2Anim_t
{
	int start;  // first frame index
	int end;    // last frame index
};

class ModelInteface
{
public:
	// Internal types
	typedef map<string, Texture*> SkinMap;
	typedef map<string, Md2Anim_t> AnimMap;

public :

	virtual bool loadTexture (const string &filename) = 0;
	virtual bool loadTexture (const string &filename, const string &alphafilename) = 0;
	virtual bool setTexture (const string &filename) = 0;
	virtual bool setTexture (const string &filename, const string &alphafilename) = 0;

	virtual void renderFrameImmediate (int frame) = 0;
	virtual void drawModelItpImmediate (int frameA, int frameB, float interp) = 0;

	virtual void renderFrameWithGLcmds (int frame) = 0;
	virtual void drawModelItpWithGLcmds (int frameA, int frameB, float interp) = 0;

	virtual void renderSelectFrameImmediate() = 0;

	void setScale (GLfloat scale) { _scale = scale; }
	float getScale () {return _scale ;}

	

	string getMd2name(){return Md2Name;}
	string getTextureName(){ return _tex->GetTexturePath(); }
	string getAlphaTextureName(){ return _tex->GetAlphaTexturePath(); }


	float GetPieceWidth(){ return m_Width; }
	float GetPieceHeight(){ return m_Height; }


	// Accessors
	const SkinMap &skins () const { return _skinIds; }
	const AnimMap &anims () const { return _anims; }

	SkinMap _skinIds;
	AnimMap _anims;

	GLfloat _scale;
	Texture *_tex;

	string Md2Name;

	GLfloat m_Width;
	GLfloat m_Height;

	
};

#endif // __MD2_H__
