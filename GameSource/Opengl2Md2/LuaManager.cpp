#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"
#include "./AttacheAble.h"
#include "LuaManager.h"

LuaManager *LuaManager::Instance = NULL;

LuaManager::LuaManager() : m_elapedtime(0)
{

	//lua_State* L = lua_open();
	lua_State* L = luaL_newstate();

	// Lua �⺻ �Լ����� �ε��Ѵ�.- print() ���
	luaopen_base(L);
	// Lua ���ڿ� �Լ����� �ε��Ѵ�.- string ���
	luaopen_string(L);

	int s = luaL_dofile(L, "MarxTextLua.lua");


	// sample1.lua �� �Լ��� ȣ���Ѵ�.
	int result = lua_tinker::call<int>(L, "OnCreate", 3, 4);

	// lua_func(3,4) �� ����� ���

	if( result == 7)
		printf("���������� Lua�� ��� �Ǿ����ϴ�.\n");


	/*
	lua_tinker::def(L,"GetSize",&LuaScriptAttached::GetSize);
	*/
	/*
	int r1 = lua_tinker::call<int>(L,"LuaTestSubject",1,2);
	printf("%d --> resualt\n", r1);

	int r2 = lua_tinker::call<int>(L,"LuaTestSubject2");
	printf("Original Value %d\n", r2);

	lua_tinker::set<int>(L,"MyLocalValue",10);
	printf("Original Value Set 10\n");

	int r3 = lua_tinker::call<int>(L,"LuaTestSubject2");
	printf("Original Value %d\n", r3);
	*/
	NowStatus = L;

	Instance = this;
}

void LuaManager::frameMove(float elapsedtime)
{
	lua_tinker::call<int>(NowStatus, "frameMove", elapsedtime);
	
}

LuaManager* LuaManager::Getinstance()
{
	if(Instance == NULL)
		Instance = new LuaManager();

	return Instance;
}

LuaManager::~LuaManager()
{
	lua_close(NowStatus);
}