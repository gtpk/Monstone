/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Md2Player.h -- Copyright (c) 2006 David Henry
// last modification: feb. 10, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Definition of MD2 Player Class.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MD2PLAYER_H__
#define __MD2PLAYER_H__

#include <vector>
#include <list>
#include <string>

#include "Md2Model.h"
#include "Md2Object.h"
#include "PieceModel.h"
#include "CommonDataType.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "../Common/VolkesInterface.h"

using std::vector;
using std::string;
using std::auto_ptr;


/////////////////////////////////////////////////////////////////////////////
//
// class Md2Player -- MD2 Player Class.
//
/////////////////////////////////////////////////////////////////////////////

class Md2Player
{
private:
	static Md2Player *inst;

public:
	// Constructors/destructor
	Md2Player ()
		throw (std::runtime_error);
	~Md2Player ();

	const int MAX_PIECE ;

	typedef auto_ptr<Md2Model> Md2ModelPtr;
	typedef std::shared_ptr<ModelInteface> Md2ModelSPtr;

	typedef std::list<Md2Object*>::iterator Md2Iter;
	typedef std::list<Md2Object*>::reverse_iterator Md2RIter;
	typedef std::list<Md2ModelSPtr>::iterator Md2MashIter;



	EXTERN::VolkesIterface* Volkes;

	static Md2Player& getInstance()
	{
		return *Md2Player::inst;
	}

	string _RootDirctory;

public:
	// Public interface
	void drawPlayerItp (bool animated, Md2Object::Md2RenderMode renderMode);
	void drawPlayerFrame (int frame, Md2Object::Md2RenderMode renderMode);
	void animate (float percent);

	// Setters and accessors
	void setScale (GLfloat scale);
	void setSkin (const string &name);
	void setAnim (const string &name);
	void setRotate(vec3_t angle );
	void setTranslate(vec3_t trance );

	void setSelectObj(int number);

	Md2Object *setNewPiece(const string &dirname,const string &md2Name,const string &textureName,COMMONDATATYPE::Vector3d eye);
	Md2Object *setNewPiece(const string &md2Name,const string &textureName,COMMONDATATYPE::Vector3d eye);
	Md2Object *setNewPieceChar(const string &md2Name,const string &textureName,COMMONDATATYPE::Vector3d eye);
	Md2Object *setNewPiece(const string &md2Name,const string &textureName,float x =0,float y=0,float z=0);
	Md2Object *setNewPiece(float Width,float Height, const string &textureName);
	Md2Object *setNewPiece(float Width,float Height, const string &textureName,const string &textureAlpha);
	Md2Object *setNewPiece(Md2Object* model);





	Md2Object *getSelectObj();

	void setSelectionTopMost();
	void setSelectionTop();
	void setSelectionBottomMost();
	void setSelectionBottom();
	void setSelectionCopy();
	void setSelectionPaste();

	void deleteSelectPiece();
	void duplicateSelectPiece();

	const string &name () const { return _name; }
	const string &currentSkin () const { return _currentSkin; }
	const string &currentAnim () const { return _currentAnim; }

	const Md2Model *playerMesh () const { return _playerMesh.get (); }
	const Md2Model *weaponMesh () const { return _weaponMesh.get (); }

	void Save();

	bool Load();

private:
	// Member variables

	std::list<Md2Object*> _WorldPiece;
	//std::vector<Md2ModelSPtr> _WorldPieceMash;
	Md2ModelPtr _playerMesh;
	Md2ModelPtr _weaponMesh;

	Md2Object _playerObject;
	Md2Object _weaponObject;

	string _name;
	string _currentSkin;
	string _currentAnim;

	
	int _NextID;
	int _Bottompos;

	int _SelectID;

	std::vector<int> m_CopyID;
	int m_copycount;
	
};

#endif // __MD2PLAYER_H__
