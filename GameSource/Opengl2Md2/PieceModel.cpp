// 사각 피스를 그리위해서 사용하는 Piece모델

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
#include "PieceModel.h"
//#include "GL/glew.h"


using std::cout;
using std::cerr;
using std::endl;


PieceModel::PieceModel(float Width,float Height) 
	: MarxObject(MARX_OBJECT_PIECEMODEL)
{
	m_Height = Height;
	m_Width = Width;
	_scale = 1.0f;
	x1 = m_Width * _scale;
	y1 = m_Height* _scale;
	x2 = (-1 * m_Width) / 2 * _scale;
	y2 = (-1 * m_Height)  / 2 * _scale;
	
	x1 = m_Width ;
	y1 = m_Height;
	x2 = (-1 * m_Width) ;
	y2 = (-1 * m_Height);

}

void PieceModel::SetPieceSize(float Width,float Height)
{
	m_Height = Height;
	m_Width = Width;

	x1 = m_Width/2 * _scale;
	y1 = m_Height/2* _scale;
	x2 = (-1 * m_Width) / 2 * _scale;
	y2 = (-1 * m_Height)  / 2 * _scale;

	x1 = m_Width;
	y1 = m_Height;
	x2 = (-1 * m_Width);
	y2 = (-1 * m_Height);
}

bool PieceModel::loadTexture (const string &filename)
{
	// Get texture manager
	Texture2DManager *texMgr = Texture2DManager::getInstance ();

	// load the texture
	Texture2D *tex = texMgr->load (filename);

	if (!tex->fail ())
	{
		if(_skinIds.find(filename) == _skinIds.end())
			_skinIds.insert (SkinMap::value_type (filename, tex));
	}

	return (!tex->fail ());
}

bool PieceModel::loadTexture (const string &filename , const string &alphafilename)
{
	
	// Get texture manager
	Texture2DManager *texMgr = Texture2DManager::getInstance ();

	// load the texture
	Texture2D *tex = texMgr->load (filename,alphafilename);

	if (!tex->fail ())
	{
		if(_skinIds.find(filename + alphafilename) == _skinIds.end())
			_skinIds.insert (SkinMap::value_type (filename + alphafilename, tex));
	}

	return (!tex->fail ());
	/*
	// Get texture manager
	Texture2DManager *texMgr = Texture2DManager::getInstance ();

	// load the texture
	Texture2D *tex = texMgr->load (filename);

	if (!tex->fail ())
	{
		if(_skinIds.find(filename) == _skinIds.end())
			_skinIds.insert (SkinMap::value_type (filename, tex));
	}

	if(tex->fail ())
		return false;

	// load the texture
	Texture2D *alphatex = texMgr->load (alphafilename);

	if (!alphatex->fail ())
	{
		if(_skinIds.find(alphafilename) == _skinIds.end())
			_skinIds.insert (SkinMap::value_type (alphafilename, alphatex));
	}
	
	return (!alphatex->fail ());
	*/
}


bool PieceModel::setTexture (const string &filename)
{
	SkinMap::iterator itor;
	itor = _skinIds.find (filename);

	if (itor != _skinIds.end ())
	{
		_tex = itor->second;
		return true;
	}
	else
	{
		_tex = NULL;
		return false;
	}
}

bool PieceModel::setTexture (const string &filename, const string &alphafilename)
{
	
	SkinMap::iterator itor;
	itor = _skinIds.find (filename + alphafilename);

	if (itor != _skinIds.end ())
	{
		_tex = itor->second;
		return true;
	}
	else
	{
		_tex = NULL;
		return false;
	}
	
	/*
	SkinMap::iterator itor;
	itor = _skinIds.find (filename );

	if (itor != _skinIds.end ())
	{
		_tex = itor->second;
	}
	else
	{
		_tex = NULL;
		return false;
	}

	itor = _skinIds.find (alphafilename);

	if (itor != _skinIds.end ())
	{
		_alphatex = itor->second;
		
	}
	else
	{
		_alphatex = NULL;
		return false;
	}*/

	return true;
}

void PieceModel::renderFrameImmediate (int frame)
{
	RenderPiece();
}
void PieceModel::drawModelItpImmediate (int frameA, int frameB, float interp)
{
	RenderPiece();
}

void PieceModel::renderFrameWithGLcmds (int frame)
{
	RenderPiece();
}
void PieceModel::drawModelItpWithGLcmds (int frameA, int frameB, float interp)
{
	RenderPiece();
}

void PieceModel::renderSelectFrameImmediate()
{
	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1.0f,0.0f,1.0f);


	glBegin(GL_LINES);

	glLineWidth(10);

	glVertex2f(x1,y1);
	glVertex2f(x2,y1);
	
	glVertex2f(x2,y1);
	glVertex2f(x2,y2);

	glVertex2f(x2,y2);
	glVertex2f(x1,y2);

	glVertex2f(x1,y2);
	glVertex2f(x1,y1);
	
	glDisable(GL_LINES);
	glColor3f(1.0f,1.0f,1.0f);
	glEnd( );
	glEnable(GL_TEXTURE_2D);

	
}

void PieceModel::RenderPiece()
{	
	// Bind to model's texture
	
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	
	//glBlendFunc(GL_ONE_MINUS_DST_COLOR ,GL_ZERO);

	if (_tex) 
		_tex->bind ();
	

	glBegin(GL_TRIANGLE_STRIP); 

		glTexCoord2f(0,0); 
		glVertex3f(x2, y2,0); 

		glTexCoord2f(0,1);
		glVertex3f(x2, y1,0); 

		glTexCoord2f(1,0);
		glVertex3f(x1, y2,0);

		glTexCoord2f(1,1);
		glVertex3f(x1, y1,0);

		//glDisable(GL_LINES);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	/*
	glBlendFunc(GL_ONE, GL_ONE);

	if (_tex)
	{
		_tex->bind ();
	}
	else
	{
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		return;
	}

	glBegin(GL_TRIANGLE_STRIP); 

		glTexCoord2f(0,0); 
		glVertex3f(x2+2, y2,0); 

		glTexCoord2f(0,1);
		glVertex3f(x2+2, y1,0); 

		glTexCoord2f(1,0);
		glVertex3f(x1+2, y2,0);

		glTexCoord2f(1,1);
		glVertex3f(x1+2, y1,0);

		//glDisable(GL_LINES);
	glEnd();
	

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	int number= 0;

	
	int options[15] ;

	int vecnum = 0;
	
	options[vecnum++] = GL_ZERO;
	options[vecnum++] = GL_ONE;
	options[vecnum++] = GL_DST_COLOR;
	options[vecnum++] = GL_SRC_COLOR;
	options[vecnum++] = GL_SRC_ALPHA_SATURATE;
	options[vecnum++] = GL_SRC_ALPHA;
	options[vecnum++] = GL_DST_ALPHA;
	options[vecnum++] = GL_ONE_MINUS_DST_COLOR;
	options[vecnum++] = GL_ONE_MINUS_SRC_COLOR;
	options[vecnum++] = GL_ONE_MINUS_SRC_ALPHA;
	options[vecnum++] = GL_ONE_MINUS_DST_ALPHA;
	
	//options[vecnum++] = GL_SRC2_RGB;
	//options[vecnum++] = GL_CONSTANT_COLOR;
	


	//RenderPiece(GL_DST_COLOR,GL_ZERO,GL_ONE,GL_ONE,number++);
	//RenderPiece(GL_ONE_MINUS_SRC_COLOR,GL_ZERO ,GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR,number++);
	
	//for(int i = 0; i<10; i++)
		//for(int ia = 0; ia<vecnum; ia++)
			//for(int ib = 0; ib<vecnum; ib++)
				//for(int ic = 0; ic<vecnum; ic++)
	
	for(int i = 0; i<vecnum; i++)
		for(int ia = 0; ia<vecnum; ia++)
			for(int ib = 0; ib<vecnum; ib++)
				for(int ic = 0; ic<vecnum; ic++)
					RenderPiece(options[i],options[ia] ,options[ib], options[ic],number++);
		*/
}

void PieceModel::RenderPiece(int value, int value2,int value3,int value4,int count)
{
	/*
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.5, 0.5, 0.5);   
	glBegin(GL_POLYGON);         //사각형
		glVertex3f(-10.5, -10.5, 0.0);
		glVertex3f(10.5, -10.5, 0.0);   
		glVertex3f(10.5, 10.5, 0.0);   
		glVertex3f(-10.5, 10.5, 0.0);      
	glEnd( );
	glEnable(GL_TEXTURE_2D);
	return;
	*   /

	int raw,cell;

	raw = count/11;
	cell = count%11;
		
	glEnable(GL_DEPTH_TEST);
	glColor4f(1,1,1,0.5);
	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(x2+ (raw*(x2 -x1)), y2+(cell*(y1-y2)),0); 
		glVertex3f(x2+ (raw*(x2 -x1)), y1+(cell*(y1-y2)),0); 
		glVertex3f(x1+ (raw*(x2 -x1)), y2+(cell*(y1-y2)),0);
		glVertex3f(x1+ (raw*(x2 -x1)), y1+(cell*(y1-y2)),0);
	glEnd();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	// Bind to model's texture
	glBlendFunc(value ,value2);

	if (_alphatex) 
		_alphatex->bind ();
	
	glBegin(GL_TRIANGLE_STRIP); 
	//glAlphaFunc(GL_LESS

		glTexCoord2f(0,0); 
		glVertex3f(x2+ (raw*(x2 -x1)), y2+(cell*(y1-y2)),0); 

		glTexCoord2f(0,1);
		glVertex3f(x2+ (raw*(x2 -x1)), y1+(cell*(y1-y2)),0); 

		glTexCoord2f(1,0);
		glVertex3f(x1+ (raw*(x2 -x1)), y2+(cell*(y1-y2)),0);

		glTexCoord2f(1,1);
		glVertex3f(x1+ (raw*(x2 -x1)), y1+(cell*(y1-y2)),0);

	glEnd();

	
	//glDisable(GL_DEPTH_TEST);
	glBlendFunc(value3, value4);
	
	if (_tex)
		_tex->bind ();

	glBegin(GL_TRIANGLE_STRIP); 

		glTexCoord2f(0,0); 
		glVertex3f(x2 + (raw*(x2 -x1)), y2+(cell*(y1-y2)),0); 

		glTexCoord2f(0,1);
		glVertex3f(x2+ (raw*(x2 -x1)), y1+(cell*(y1-y2)),0); 

		glTexCoord2f(1,0);
		glVertex3f(x1+ (raw*(x2 -x1)), y2+(cell*(y1-y2)),0);

		glTexCoord2f(1,1);
		glVertex3f(x1+ (raw*(x2 -x1)), y1+(cell*(y1-y2)),0);

	glEnd();
	//glBlendFunc(GL_ZERO, GL_ZERO);
	
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	

	glColor3f(1.0f,1.0f,1.0f);
	//glBindTexture (GL_TEXTURE_2D, 0);
	*/
}