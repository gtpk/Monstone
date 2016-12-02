#pragma once
#include "./MarxObject.h"
#include "LuaManager.h"

class MarxObject;

class AttacheAble 
{
public:
	AttacheAble(void);
	virtual ~AttacheAble(void);

	virtual void OnAttach(MarxObject* object) = 0;
	

private:
	
};

