/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Md2Player.cpp -- Copyright (c) 2006 David Henry
// last modification: feb. 25, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Implementation of MD2 Player class.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>

#else
#include "dirent.h"
#endif


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>

#include "Opengl2md2.h"

#include "MarxWorld.h"
#include "Md2Object.h"

#include "Texture.h"
#include "PieceModel.h"
#include "../Common/VolkesInterface.h"
#include "ProjectLoader.h"
#include "LuaScriptAttached.h"

#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"

//#include "Opengl2md2.h"


using std::cout;
using std::cerr;
using std::endl;

/////////////////////////////////////////////////////////////////////////////
//
// class Md2Player implementation.
//
/////////////////////////////////////////////////////////////////////////////

// static 초기화는 이렇게 이루어지는것!
MarxWorld *MarxWorld::inst = NULL;

// --------------------------------------------------------------------------
// Md2Player::Md2Player
//
// Constructor.  Read a MD2 player from directory.
// --------------------------------------------------------------------------

MarxWorld::MarxWorld()
throw (std::runtime_error)
	: _playerMesh(NULL), _weaponMesh(NULL), MAX_PIECE(20), _NextID(101), _Bottompos(99)
{
	_RootDirctory = ProjectLoader::getinstance()->GetProjectPath();

	MarxWorld::inst = this;

	ObjectManager* m_ObjectManager = ObjectManager::GetInstance();


	//Md2Object * obj = setNewPiece("chr_01.md2", "chr_01.tga", Opengl2md2::getInstance().eye);
	//
	//if (obj != NULL)
	//{
	//	//_playerMesh = Md2ModelPtr((Md2Model*)obj->model());
	//	m_ObjectManager->ReplaceMarxObject("MainCharacter", obj);
	//	obj->setScale(0.05);
	//
	//	//3.5 -331 z 는 아무거나
	//	obj->setRotate(3.5, -331, 0);
	//	LuaScriptAttached * attach = new LuaScriptAttached();
	//	obj->OnAttech(attach);
	//}
	//	
	


}



// --------------------------------------------------------------------------
// Md2Player::~Md2Player
//
// Destructor.
// --------------------------------------------------------------------------

MarxWorld::~MarxWorld ()
{
}


// --------------------------------------------------------------------------
// Md2Player::drawPlayerItp
//
// Draw player objects with interpolation.
// --------------------------------------------------------------------------

void MarxWorld::drawPlayerItp (bool animated, Md2Object::Md2RenderMode renderMode)
{
	
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(; md2begin != md2End ;  ++md2begin)
	{
		Md2Object* node = (Md2Object*)*md2begin;

		node->drawObjectItp (animated, renderMode);
	}

	if (_playerMesh.get ())
	{
		_playerMesh->setTexture (_currentSkin);
		_playerObject.drawObjectItp (animated, renderMode);
	}
	if (_weaponMesh.get ())
		_weaponObject.drawObjectItp (animated, renderMode);


}


// --------------------------------------------------------------------------
// Md2Player::drawPlayerFrame
//
// Draw player objects at a given frame.
// --------------------------------------------------------------------------

void MarxWorld::drawPlayerFrame (int frame, Md2Object::Md2RenderMode renderMode)
{

	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(; md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		node->drawObjectFrame (frame, renderMode);
	}
	
	
}



void MarxWorld::setSelectObj(int number) 
{
	_SelectID = number; 

	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			node->setSelect(true);
			if(Volkes != NULL)
				Volkes->SetSelection(node);
		}
		else
		{
			node->setSelect(false);
		}
	}
}


// --------------------------------------------------------------------------
// Md2Player::animate
//
// Animate player objects.
// --------------------------------------------------------------------------

void MarxWorld::animate (GLfloat percent)
{

	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
	
		if(node->GetName() == "MainCharacter")
		{
			node->animate(percent);
		}
	}

}


// --------------------------------------------------------------------------
// Md2Player::setScale
//
// Scale model objects.
// --------------------------------------------------------------------------

void MarxWorld::setScale (GLfloat scale)
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(; md2begin != md2End ;  md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		//node->setScale (scale);
		ModelInteface* model = node->model();
		if(model)
		{
			if(node->getName() == _SelectID)
				model->setScale(scale);
		}
	}
}


// --------------------------------------------------------------------------
// Md2Player::setSkin
//
// Set player skin.
// --------------------------------------------------------------------------

void MarxWorld::setSkin (const string &name)
{
	if(100 == _SelectID)
		_currentSkin = name;
	
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(; md2begin != md2End ;  md2begin++)
	{
		
		Md2Object* node = ((Md2Object*)*md2begin);
		ModelInteface* model = node->model();
		if(model)
		{
			if(node->getName() == _SelectID)
				model->setTexture (name);
		}
	}

	
}


// --------------------------------------------------------------------------
// Md2Player::setAnim
//
// Set current player animation.
// --------------------------------------------------------------------------

void MarxWorld::setAnim (const string &name)
{
	if (_weaponMesh.get ())
	{
		_weaponObject.setAnim (name);
		_currentAnim = name;
	}

	if (_playerMesh.get ())
	{
		_playerObject.setAnim (name);
		_currentAnim = name;
	}
}

void MarxWorld::setRotate(vec3_t angle)
{
	/*
	if (_weaponMesh.get ())
	{
		_weaponObject.setRotate (angle);
	}

	if (_playerMesh.get ())
	{
		_playerObject.setRotate (angle);
	}*/

	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(; md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);

		if(node->getName() == _SelectID)
		{
			node->setRotate (angle);
		}
	}
}

void MarxWorld::setTranslate(vec3_t trance )
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			node->setTranslate (trance);
		}
	}

}


Md2Object * MarxWorld::getSelectObj()
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			return node;
		}
	}
	return NULL;
}

void MarxWorld::setSelectionTopMost()
{
	Md2RIter md2begin = _WorldPiece.rbegin();
	Md2RIter md2End = _WorldPiece.rend();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);

		if(node->getName() == _SelectID)
		{
			if( _WorldPiece.rbegin() == md2begin)
				return;
			md2begin = Md2RIter(_WorldPiece.erase((++md2begin).base()));
			_WorldPiece.push_back(node);
			return;
		}
	}
}
void MarxWorld::setSelectionTop()
{
	Md2RIter md2begin = _WorldPiece.rbegin();
	Md2RIter md2End = _WorldPiece.rend();
	
	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			if(md2begin == _WorldPiece.rbegin())
				return; // 맨 위면 안해도 되요.

			md2begin = Md2RIter(_WorldPiece.erase((++md2begin).base()));
			_WorldPiece.insert(md2begin.base(),node);
			return;
		}
	}
}
void MarxWorld::setSelectionBottomMost()
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			md2begin =_WorldPiece.erase(md2begin);
			_WorldPiece.push_front(node);
			return;
		}
	}
	
}
void MarxWorld::setSelectionBottom()
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();

	for(;md2begin != md2End ; md2begin++)
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			if(md2begin == _WorldPiece.begin())
				return; // 맨 밑이면 안해도 되요.

			md2begin =_WorldPiece.erase(md2begin);
			md2begin--;
			_WorldPiece.insert(md2begin,node);
			return;
		}
	}
}

void MarxWorld::deleteSelectPiece()
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();
	for(; md2begin != md2End ; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			delete node;
			md2begin = _WorldPiece.erase(md2begin);

			return;
		}
		md2begin++;

	}
}

void MarxWorld::setSelectionCopy()
{
	m_copycount = 0;
	this->m_CopyID.clear();

	this->m_CopyID.push_back(_SelectID);
}

void MarxWorld::setSelectionPaste()
{
	m_copycount++;
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();
	for(; md2begin != md2End ; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);

		std::vector<int>::iterator  Cid = m_CopyID.begin();
		std::vector<int>::iterator  Eid = m_CopyID.end();
		for(; Cid != Eid ; )
		{
			if(node->getName() == *Cid)
			{
				setNewPiece(node);
			}
			Cid++;
		}
		md2begin++;
	}
	
	

}

void MarxWorld::duplicateSelectPiece()
{
	Md2Iter md2begin = _WorldPiece.begin();
	Md2Iter md2End = _WorldPiece.end();
	for(; md2begin != md2End ; )
	{
		Md2Object* node = ((Md2Object*)*md2begin);
		if(node->getName() == _SelectID)
		{
			setNewPiece(node);
			return;
		}
		md2begin++;

	}
}




// --------------------------------------------------------------------------
// Md2Player::setNewPiece
//
// 피스 등록하는 함수
// --------------------------------------------------------------------------


Md2Object *MarxWorld::setNewPiece(const string &dirname,const string &md2Name,const string &textureName,COMMONDATATYPE::Vector3d eye)
{
	std::ifstream pieceifs;

	string path = dirname + "/" + md2Name;
	pieceifs.open (path.c_str (), std::ios::binary);

	if (!pieceifs.fail ())
	{
		pieceifs.close ();
		return false;
	}

	GLfloat pos = -10;

	Md2Object* obj = new Md2Object();
	//_WorldPiece.push_back()
	obj->setName(_NextID);
	_NextID++;
	obj->setModel (path,textureName);
	obj->setRotate(0,90,90);
	obj->setTranslate(0,pos,pos/2);
	pos+=2;
	obj->setScale(0.1);
	_WorldPiece.push_back(obj);

	// Set first skin as default skin
	// 피스는 에니메이션이 없다고 가정한다.
	//_currentSkin = Model->skins().begin ()->first;
	//_currentAnim = obj->currentAnim ();

	return obj;
}

Md2Object *MarxWorld::setNewPiece(const string &md2Name, const string &textureName, COMMONDATATYPE::Vector3d eye)
{
	std::ifstream pieceifs;

	string path = _RootDirctory + "/" + md2Name;
	pieceifs.open(path.c_str(), std::ios::binary);

	if (!pieceifs.fail())
	{
		pieceifs.close();
		return false;
	}

	GLfloat pos = -10;

	Md2Object* obj = new Md2Object();
	//_WorldPiece.push_back()
	obj->setName(_NextID);
	_NextID++;
	obj->setModel(path, textureName);
	obj->setRotate(0, 90, 90);
	obj->setTranslate(0, pos, pos / 2);
	pos += 2;
	obj->setScale(0.1);
	_WorldPiece.push_back(obj);

	// Set first skin as default skin
	// 피스는 에니메이션이 없다고 가정한다.
	//_currentSkin = Model->skins().begin ()->first;
	//_currentAnim = obj->currentAnim ();

	return obj;
}

Md2Object *MarxWorld::setNewPieceChar(const string &md2Name, const string &textureName, COMMONDATATYPE::Vector3d eye)
{
	std::ifstream pieceifs;

	string path = _RootDirctory + "/"+ md2Name;
	pieceifs.open (path.c_str (), std::ios::binary);

	if (pieceifs.fail ())
	{
		return false;
	}
	pieceifs.close ();

	Md2Object* obj = new Md2Object();
	//_WorldPiece.push_back()
	obj->setName(_NextID);
	_NextID++;
	obj->setModel (md2Name,textureName);
	obj->setRotate(0,90,90);
	obj->setScale(0.025);
	obj->setTranslate(eye.x+5,eye.y+5,(_NextID-1200));

	_WorldPiece.push_back(obj);

	return obj;
}

Md2Object *MarxWorld::setNewPiece(const string &md2Name,const string &textureName,float x,float y,float z)
{
	COMMONDATATYPE::Vector3d data;
	data.x = x;
	data.y = y;
	data.z = z;
	return setNewPiece(md2Name,textureName,data);
}

Md2Object *MarxWorld::setNewPiece(float Width,float Height , const string &textureName)
{


	Md2Object* obj = new Md2Object();
	//_WorldPiece.push_back()
	obj->setName(_NextID);
	_NextID++;
	obj->setModel (Width,Height,textureName);
	obj->setRotate(0,90,90);
	obj->setScale(0.1);

	obj->setTranslate(
		Opengl2md2::getInstance().eye.x,
		Opengl2md2::getInstance().eye.y,
		(_NextID-1100));
	//obj->setTranslate(Opengl2md2::getInstance().eye.x,Opengl2md2::getInstance().eye.y,Opengl2md2::getInstance().eye.z);

	
	_WorldPiece.push_back(obj);

	return obj;
}

Md2Object *MarxWorld::setNewPiece(Md2Object* model)
{
	Md2Object* obj = new Md2Object();
	//_WorldPiece.push_back()
	
	obj->setModel (model->model());

	obj->setName(_NextID);
	_NextID++;

	obj->setTranslate(
		Opengl2md2::getInstance().eye.x + m_copycount*0.1,
		Opengl2md2::getInstance().eye.y + m_copycount*0.1,
		(_NextID-1100));

	
	obj->setRotate(0,90,model->getRotate()[2]);
	
	
	_WorldPiece.push_back(obj);

	return obj;

}


Md2Object *MarxWorld::setNewPiece(float Width,float Height, const string &textureName,const string &textureAlpha)
{

	
	Md2Object* obj = new Md2Object();
	obj->setName(_NextID);
	_NextID++;
	obj->setModel (Width,Height,textureName,textureAlpha );
	obj->setRotate(0,90,90);
	obj->setScale(0.1);
	obj->setTranslate(
		Opengl2md2::getInstance().eye.x,
		Opengl2md2::getInstance().eye.y,
		(_NextID-1100));

	
	_WorldPiece.push_back(obj);
	LuaScriptAttached * attach = new LuaScriptAttached();

	obj->OnAttech(attach);


	return obj;
}


void MarxWorld::Save()
{
	TiXmlDocument doc;  
	TiXmlElement* msg;

	//문서 설정
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	
	doc.LinkEndChild( decl );
	// Root 만들자
	TiXmlElement * root = new TiXmlElement( "MinMonstersMap" );  
	doc.LinkEndChild( root ); 

	root->SetAttribute("name","Example");
	root->SetAttribute("RootFolder",_RootDirctory.c_str());

	//경고 문구삽입
	//TiXmlComment * comment = new TiXmlComment();
	//comment->SetValue("자동 완성된 코드 이므로 직접 수정 하지 마시오." );  
	//root->LinkEndChild( comment );

	TiXmlElement * MapPieces = new TiXmlElement( "MapPieces" );  
	root->LinkEndChild( MapPieces );  

	{
		Md2Iter md2begin = _WorldPiece.begin();
		Md2Iter md2End = _WorldPiece.end();

		for(;md2begin != md2End ; md2begin++)
		{

			Md2Object* node = ((Md2Object*)*md2begin);	

			TiXmlElement * Piece;
			Piece = new TiXmlElement( "Piece" );  
			MapPieces->LinkEndChild( Piece );  
			Piece->SetAttribute("Name", node->getName());
			Piece->SetAttribute("TextureName", node->model()->getTextureName().c_str());
			Piece->SetAttribute("ModelName",node->model()->getMd2name().c_str());
			Piece->SetDoubleAttribute("Scale",node->scale());
			//Piece->SetDoubleAttribute("x",node.get);

			TiXmlElement * Trancerate;
			Trancerate = new TiXmlElement( "Trancerate" );
			Piece->LinkEndChild(Trancerate);
			Trancerate->SetDoubleAttribute("x", node->m_translate[0]);
			Trancerate->SetDoubleAttribute("y", node->m_translate[1]);
			Trancerate->SetDoubleAttribute("z", node->m_translate[2]);

			TiXmlElement * Rotation;
			Rotation = new TiXmlElement( "Rotation" );
			Piece->LinkEndChild(Rotation);
			Rotation->SetDoubleAttribute("x", node->m_rotation[0]);
			Rotation->SetDoubleAttribute("y", node->m_rotation[1]);
			Rotation->SetDoubleAttribute("z", node->m_rotation[2]);
		}	
	}

	doc.SaveFile("text.xml");
}

bool MarxWorld::Load()
{
	TiXmlDocument doc( "text.xml" );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		// 파일이 없음..!!
		return false ;
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
	}


	TiXmlDeclaration* declar = doc.ToDeclaration();
	if(declar != NULL)
	{
		if(declar->Version() != "1.0")
		{
			// 버전이 일치 하지 않음
			return false;
		}
	}
	
	TiXmlNode* MapNode;

	MapNode = doc.FirstChild("MinMonstersMap"); 

	TiXmlElement* MinMonstersMap = MapNode->ToElement();
	_RootDirctory = MinMonstersMap->Attribute("RootFolder");

	TiXmlNode * MapPieces = MapNode->FirstChild( "MapPieces" );  

	
	{
		TiXmlNode* Piece = MapPieces->FirstChild("Piece");

		for(; Piece!=NULL ;Piece = Piece->NextSibling())
		{ 
			int name=101;
			float Scale = 0.1;
			
		
			TiXmlElement* pelement = Piece->ToElement();
			pelement->Attribute("Name",&name);
			const char* TextureName = pelement->Attribute("TextureName");
			const char* Md2Name = pelement->Attribute("ModelName");

			pelement->QueryFloatAttribute("Scale",&Scale);

			
			
			vec3_t m_translate;

			TiXmlNode* Trancerate = Piece->FirstChild("Trancerate");
			TiXmlElement* pTracerate = Trancerate->ToElement();
			pTracerate->QueryFloatAttribute("x",&m_translate[0]);
			pTracerate->QueryFloatAttribute("y",&m_translate[1]);
			pTracerate->QueryFloatAttribute("z",&m_translate[2]);

			vec3_t m_rotation;
			TiXmlNode* Rotation = Piece->FirstChild("Rotation");
			TiXmlElement* pRotation = Rotation->ToElement();
			pRotation->QueryFloatAttribute("x",&m_rotation[0]);
			pRotation->QueryFloatAttribute("y",&m_rotation[1]);
			pRotation->QueryFloatAttribute("z",&m_rotation[2]);


			std::ifstream pieceifs;

			string path = Md2Name;
			pieceifs.open (path.c_str (), std::ios::binary);

			if (pieceifs.fail ())
			{
				pieceifs.close ();
				continue;
			}
			/*
			else
			{
				// 메시 불러오기
				Model = Md2ModelSPtr(new Md2Model (path));
				_WorldPieceMash.push_back( Model );

				// 텍스쳐 불러오기
				if(Model->setTexture(TextureName) == false)
				{
					Model->loadTexture(TextureName);
					Model->setTexture (TextureName);
				}		
			}

			*/
			// 모델이 불러졌는지 확인하고 없으면 에러
			

			GLfloat pos = -10;

			Md2Object* obj = new Md2Object();
			//_WorldPiece.push_back()
			obj->setName(name);
			obj->setModel (path,TextureName);
			obj->setRotate(m_rotation[0],m_rotation[1],m_rotation[2]);
			obj->setTranslate(m_translate[0],m_translate[1],m_translate[2]);
			obj->setScale(Scale);
			_WorldPiece.push_back(obj);
		}	
	}
	
	return false;

}