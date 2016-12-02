#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"
#include "./AttacheAble.h"

class TestFunctionClass
{
};

class LuaScriptAttached : public AttacheAble
{

public:
	LuaScriptAttached();
	~LuaScriptAttached();

	virtual void OnAttach(MarxObject* object);

	

	int GetSize();
private:

	LuaManager* NowStatus;

};

