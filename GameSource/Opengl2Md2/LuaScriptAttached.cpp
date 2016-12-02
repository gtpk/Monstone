#include "../Externallib/LuaJit/Header/lua.hpp"
#include "../Externallib/LuaJit/Header/lua_tinker.h"

#include "./AttacheAble.h"
#include "LuaScriptAttached.h"

#include "Md2Model.h"
#include "PieceModel.h"
#include "Md2Object.h"


LuaScriptAttached::LuaScriptAttached()
	: NowStatus(NULL)
{

	NowStatus = LuaManager::Getinstance();
    
}

int LuaScriptAttached::GetSize()
{
	return 0;
}


void LuaScriptAttached::OnAttach(MarxObject* object)
{

	lua_State* L = NowStatus->NowStatus;
	// base Ŭ������ Lua �� �߰��Ѵ�.
	lua_tinker::class_add<MarxObject>(L, "MarxObject");

	// base �� �Լ��� ����Ѵ�.
	lua_tinker::class_def<MarxObject>(L, "is_test", &MarxObject::is_test);

	

	int result = lua_tinker::call<int>(L, "LuaTestSubject",object->GetName().c_str());

	if( result == 10)
		printf("���������� ����\n");


	switch (object->GetType())
	{
	case MARX_OBJECT_MD2_MODEL:
		{
			printf("MD2 �� �߰���\n");
			Md2Model* md2model =  static_cast<Md2Model*>(object);
		}
		break;
	case MARX_OBJECT_PIECEMODEL:
		{
			printf("�ǽ� �߰���\n");
			PieceModel* piecemodel =  static_cast<PieceModel*>(object);
		}
		break;
	case MARX_OBJECT_OBJECT:
		{
			printf("����ũ�� ��ü �߰���\n");
			//Md2Model* md2model =  static_cast<Md2Model*>(object);
		}
		break;
	case MARX_OBJECT_MD2_OBJECT:
		{

			printf("���� ������Ʈ �߰���\n");
			Md2Object* piecemodel =  static_cast<Md2Object*>(object);

			// test Ŭ������ Lua �� �߰��Ѵ�.
			lua_tinker::class_add<Md2Object>(L, "Md2Object");

			// test �� base �� ��� �޾����� �˷��ش�.
			lua_tinker::class_inh<Md2Object, MarxObject>(L);

			
			lua_tinker::class_def<Md2Object>(L, "setRotate", &Md2Object::setRotate_Lua);
			lua_tinker::class_def<Md2Object>(L, "getRotateX",&Md2Object::getRotateX_Lua);
			lua_tinker::class_def<Md2Object>(L, "getRotateY",&Md2Object::getRotateY_Lua);
			lua_tinker::class_def<Md2Object>(L, "getRotateZ",&Md2Object::getRotateZ_Lua);

			lua_tinker::class_def<Md2Object>(L, "setTranslate", &Md2Object::setTranslate_Lua);
			lua_tinker::class_def<Md2Object>(L, "getTranslateX",&Md2Object::getTranslateX_Lua);
			lua_tinker::class_def<Md2Object>(L, "getTranslateY",&Md2Object::getTranslateY_Lua);
			lua_tinker::class_def<Md2Object>(L, "getTranslateZ",&Md2Object::getTranslateZ_Lua);

			lua_tinker::set(L, object->GetName().c_str(), piecemodel);

		}
		break;
	default:
		printf("��ϵ��� ���� Ÿ�� �߰���\n");
		break;
	} 

	
	
}

LuaScriptAttached::~LuaScriptAttached()
{
	
}
