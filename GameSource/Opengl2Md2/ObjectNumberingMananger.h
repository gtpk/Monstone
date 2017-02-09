#pragma once
#include <map>
#include <unordered_map>
#include "MarxObject.h"
using namespace std;

class ObjectNumberingMananger
{
public:
	ObjectNumberingMananger();
	~ObjectNumberingMananger();

private:
	static ObjectNumberingMananger* inst;
public:
	static ObjectNumberingMananger* getInstance()
	{
		if (inst == NULL)
		{
			inst = new ObjectNumberingMananger();
		}
		return inst;
	}

	bool isExsistNumber(int number);
	bool UseNumber(int number, MarxObject* obj);
	bool UnUseNumber(int number, MarxObject* obj);
	int getNumber(MarxObject* obj);
	MarxObject* GetMarxObject(int Name);
private:
	// Member variables
	std::map<int, bool> CheckMap;
	int _NextID;
	std::map<int, MarxObject*> ObjectList;
	

};
