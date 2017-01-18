#include "ObjectNumberingMananger.h"

ObjectNumberingMananger* ObjectNumberingMananger::inst = NULL; 

ObjectNumberingMananger::ObjectNumberingMananger() : _NextID(101)
{
}

ObjectNumberingMananger::~ObjectNumberingMananger()
{
}

int ObjectNumberingMananger::getNumber()
{
	while (isExsistNumber(_NextID))
		_NextID++;
	int value = _NextID;
	_NextID++;
	return value;
}
bool ObjectNumberingMananger::UnUseNumber(int number)
{
	CheckMap[number] = false;
	std::map<int, bool>::iterator _f = CheckMap.find(number);
	if (_f != CheckMap.end())
	{
		CheckMap.erase(_f);
	}
	return true;
}
bool ObjectNumberingMananger::UseNumber(int number)
{
	if (isExsistNumber(number))
	{
		return false;
	}
	CheckMap[number] = true;
}
bool ObjectNumberingMananger::isExsistNumber(int number)
{
	std::map<int, bool>::iterator _f = CheckMap.find(number);
	if (_f != CheckMap.end())
		return CheckMap[number]; //존재 해도 데이터가 true일수있다.
	return false;
}