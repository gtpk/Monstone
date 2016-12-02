#include "MarxObject.h"
#include "ObjectManager.h"


MarxObject::MarxObject(MARXOBJECT_TYP_ENUM type)
	: m_name("") , objtype(type)
{
	m_ObjectManager = ObjectManager::GetInstance();
	m_ObjectManager->ObjectdefaultName(this);
}


MarxObject::~MarxObject(void)
{
	m_ObjectManager->DeleteMarxObject(m_name);
}

bool MarxObject::OnAttech(AttacheAble* _pattachable)
{
	if(_pattachable == NULL)
		return false;

	m_AttachChild.push_back(_pattachable);
	_pattachable->OnAttach(this);

}

const char* MarxObject::is_test(const char* _name)
{
	printf("%s´Â ºıºıÀÌ´Ù\n",_name);
	return m_name.c_str(); 
}