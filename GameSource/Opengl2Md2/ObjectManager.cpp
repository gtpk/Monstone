
#include "ObjectManager.h"
#include "Stringformat.h"
#include <map>


ObjectManager* ObjectManager::m_instance = NULL;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::PushMarxObject(const std::string _Name, MarxObject * pObj)
{
	if(isExsistName(_Name))
		return false;

	printf("%s 가 성공적으로 등록 되었습니다.\n",_Name.c_str());
	m_ObjectNameList[_Name] = pObj;

	pObj->SetName(_Name);

	return true;
}

bool ObjectManager::isExsistName(const std::string _Name)
{
	OBJECT_NAME_MAP_ITOR itor = m_ObjectNameList.find(_Name);
	if(itor != m_ObjectNameList.end())
	{
		//printf("같은 이름의 Object가 있습니다.");
		return true;
	}
	return false;
}

bool ObjectManager::DeleteMarxObject(const std::string _Name)
{
	printf("%s 가 성공적으로 삭제 되었습니다.\n",_Name.c_str());
	OBJECT_NAME_MAP_ITOR itor = m_ObjectNameList.find(_Name);
	if(itor != m_ObjectNameList.end())
	{
		m_ObjectNameList.erase(itor);
		return true;
	}
	return false;
}

bool ObjectManager::ReplaceMarxObject(const std::string _Name, MarxObject * pObj)
{
	DeleteMarxObject(pObj->GetName());
	PushMarxObject(_Name,pObj);

	printf("%s가 변경되어 등록 되었습니다.\n",_Name.c_str());

	return true;
}


bool ObjectManager::ObjectdefaultName(MarxObject * pObj)
{
	//이 이름으로 객체를 찾을순 없다!
	pObj->SetName("(MarxObject)");
	return true;
	//int duplicate = 0;
	//std::string UntitleName;
	//
	//int _size = m_ObjectNameList.size();
	//UntitleName = format("MarxObject%d",_size);
	//
	//while(true)
	//{
	//	if(PushMarxObject(UntitleName,pObj) == false)
	//	{
	//		duplicate++;
	//		UntitleName = format("MarxObject%d(%d)",m_ObjectNameList.size(),duplicate);
	//	}
	//	else
	//	{
	//		pObj->SetName(UntitleName);
	//		return true;
	//	}
	//}
}

