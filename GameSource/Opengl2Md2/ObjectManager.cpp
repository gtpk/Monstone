
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

	printf("%s �� ���������� ��� �Ǿ����ϴ�.\n",_Name.c_str());
	m_ObjectNameList[_Name] = pObj;

	pObj->SetName(_Name);

	return true;
}

bool ObjectManager::isExsistName(const std::string _Name)
{
	OBJECT_NAME_MAP_ITOR itor = m_ObjectNameList.find(_Name);
	if(itor != m_ObjectNameList.end())
	{
		//printf("���� �̸��� Object�� �ֽ��ϴ�.");
		return true;
	}
	return false;
}

bool ObjectManager::DeleteMarxObject(const std::string _Name)
{
	printf("%s �� ���������� ���� �Ǿ����ϴ�.\n",_Name.c_str());
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

	printf("%s�� ����Ǿ� ��� �Ǿ����ϴ�.\n",_Name.c_str());

	return true;
}


bool ObjectManager::ObjectdefaultName(MarxObject * pObj)
{
	//�� �̸����� ��ü�� ã���� ����!
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

