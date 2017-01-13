#pragma once

#include "AttacheAble.h"
#include "ObjectManager.h"

#include <vector>
#include <string>


class AttacheAble;
class ObjectManager;

typedef std::vector<AttacheAble*> VEC_ATTACH;

enum MARXOBJECT_TYP_ENUM
{
	MARX_OBJECT_OBJECT,
	MARX_OBJECT_MD2_MODEL,
	MARX_OBJECT_PIECEMODEL,
	MARX_OBJECT_ANIMAION,
	MARX_OBJECT_MD2_OBJECT,
	MARX_OBJECT_CHARICTOR,
	MARX_OBJECT_UI,
};

class MarxObject
{

public:
	MarxObject(MARXOBJECT_TYP_ENUM type);
	~MarxObject(void);
	
	virtual bool OnAttech(AttacheAble* _pattachable);

	VEC_ATTACH m_AttachChild;

	std::string m_MarxObjectName;

	ObjectManager * m_ObjectManager;

	void SetName(std::string name) { m_name = name; }

	const char* is_test(const char* _name);

	std::string GetName() { return m_name; }

	MARXOBJECT_TYP_ENUM GetType(){ return objtype; }

protected:
	MARXOBJECT_TYP_ENUM objtype;
private:
	std::string m_name;
	

};

