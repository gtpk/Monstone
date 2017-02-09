#include "ObjectNumberingMananger.h"

ObjectNumberingMananger* ObjectNumberingMananger::inst = NULL; 

ObjectNumberingMananger::ObjectNumberingMananger() : _NextID(101)
{
}

ObjectNumberingMananger::~ObjectNumberingMananger()
{
}

int ObjectNumberingMananger::getNumber(MarxObject* obj)
{
	while (isExsistNumber(_NextID))
		_NextID++;
	int value = _NextID;
	_NextID++;
	ObjectList[value] = obj;
	return value;
}
bool ObjectNumberingMananger::UnUseNumber(int number, MarxObject* obj)
{
	CheckMap[number] = false;
	std::map<int, bool>::iterator _f = CheckMap.find(number);
	if (_f != CheckMap.end())
	{
		CheckMap.erase(_f);
	}

	std::map<int, MarxObject*>::iterator _f1 = ObjectList.find(number);
	if (_f1 != ObjectList.end())
	{
		ObjectList.erase(_f1);
	}

	return true;
}
bool ObjectNumberingMananger::UseNumber(int number, MarxObject* obj)
{
	if (isExsistNumber(number))
	{
		return false;
	}
	CheckMap[number] = true;
	ObjectList[number] = obj;
}
bool ObjectNumberingMananger::isExsistNumber(int number)
{
	std::map<int, bool>::iterator _f = CheckMap.find(number);
	if (_f != CheckMap.end())
		return CheckMap[number]; //존재 해도 데이터가 true일수있다.
	return false;
}

MarxObject* ObjectNumberingMananger::GetMarxObject(int Name)
{
	if (ObjectList[Name] == NULL)
		return NULL;
	//printf("Atlasfind %s \n", Name.c_str());
	return ObjectList[Name];
}