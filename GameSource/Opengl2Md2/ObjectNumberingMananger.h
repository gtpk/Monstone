#pragma once

#include <map>

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
	bool UseNumber(int number);
	bool UnUseNumber(int number);
	int getNumber();
private:
	// Member variables
	std::map<int, bool> CheckMap;
	int _NextID;


};
