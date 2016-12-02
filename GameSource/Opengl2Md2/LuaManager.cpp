#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"
#include "./AttacheAble.h"
#include "LuaManager.h"

LuaManager *LuaManager::Instance = NULL;

LuaManager::LuaManager() : m_elapedtime(0)
{

	//lua_State* L = lua_open();
	lua_State* L = luaL_newstate();

	// Lua 기본 함수들을 로드한다.- print() 사용
	luaopen_base(L);
	// Lua 문자열 함수들을 로드한다.- string 사용
	luaopen_string(L);

	int s = luaL_dofile(L, "MarxTextLua.lua");


	// sample1.lua 의 함수를 호출한다.
	int result = lua_tinker::call<int>(L, "OnCreate", 3, 4);

	// lua_func(3,4) 의 결과물 출력

	if( result == 7)
		printf("성공적으로 Lua가 등록 되었습니다.\n");


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