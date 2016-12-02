#pragma once
#include "MarxObject.h"

#include <map>


class MarxObject;

class ObjectManager
{
public:

	typedef std::map<std::string, MarxObject*> OBJECT_NAME_MAP;
	typedef OBJECT_NAME_MAP::iterator OBJECT_NAME_MAP_ITOR;


public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* GetInstance()
	{
		if(m_instance == NULL)
		{
			m_instance = new ObjectManager();
		}
		return m_instance;
	}
	

	OBJECT_NAME_MAP m_ObjectNameList;

	bool PushMarxObject(const std::string _Name, MarxObject * pObj);

	bool isExsistName(const std::string _Name);

	bool DeleteMarxObject(const std::string _Name);

	bool ReplaceMarxObject(const std::string _Name, MarxObject * pObj);

	bool ObjectdefaultName(MarxObject * pObj);

	

private:
	static ObjectManager* m_instance;
};

