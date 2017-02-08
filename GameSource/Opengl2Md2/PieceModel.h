#ifndef  __PIECEMODEL_H__
#define	__PIECEMODEL_H__
#include "Texture.h"
#include "ModelInterface.h"
#include "MarxObject.h"
#include <string>

using std::string;


class PieceModel  : public ModelInteface , public MarxObject
{
public :
	PieceModel(float Width,float Height);

	// Internal types
	typedef map<string, Texture*> SkinMap;

	bool loadTexture (const string &filename);
	bool loadTexture (const string &filename, const string &alphafilename);
	bool setTexture (const string &filename);
	bool setTexture (const string &filename, const string &alphafilename);

	void SetPieceSize(float Width,float Height);

	void renderFrameImmediate (int frame);
	void drawModelItpImmediate (int frameA, int frameB, float interp);

	void renderFrameWithGLcmds (int frame);
	void drawModelItpWithGLcmds (int frameA, int frameB, float interp);

	void renderSelectFrameImmediate(int Numbers[]);

	void RenderPiece();
	void RenderPiece(int value, int value2,int value3,int value4, int count);
	void RenderRect(float x,float y, int name);

public:

private :

	GLfloat x1;
	GLfloat x2;
	GLfloat y1;
	GLfloat y2;

	string Md2Name;


public :
	void Render();

};
#endif