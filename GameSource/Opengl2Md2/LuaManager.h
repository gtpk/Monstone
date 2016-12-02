/*
 *  루아 전체 매니저!! 부왁!!
 */

#pragma once
#include "../Externallib/LuaJit/Header/lua.hpp"

class LuaManager
{
public:
	LuaManager();
	~LuaManager();

	void frameMove(float elapsedtime);

	lua_State* NowStatus;

	static LuaManager* Getinstance();

	float m_elapedtime;

private:

	static LuaManager* Instance;

};

