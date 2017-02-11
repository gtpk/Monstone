#include "SelectableObject.h"
#include "ObjectNumberingMananger.h"
#include "ObjectMove.h"
#include "ImageControl.h"

SelectableObject::SelectableObject() :MarxObject(MARX_OBJECT_MD2_OBJECT)
{
	_currentName = ObjectNumberingMananger::getInstance()->getNumber(this);

	for (int i = 0; i < 8; i++)
	{
		SelectNumbers[i] = ObjectNumberingMananger::getInstance()->getNumber(this);
		EdgeTarget edge;
		edge.direction = i;
		edge.id = SelectNumbers[i];
		edge.obj = this;
		slelectList[i] = edge;
	}
}

SelectableObject::~SelectableObject()
{
	std::list<SelectableObject*>::iterator _iter = child.begin();
	while (_iter != child.end())
	{
		SelectableObject* var = *_iter;
		delete (var);
		_iter++;

		
	}
	//자기자신 삭제 알림
	Md2Object* node = dynamic_cast<Md2Object*>(this);
	if (node != NULL)
	{
		if (MarxWorld::getInstance().Volkes != NULL)
			MarxWorld::getInstance().Volkes->DeletePiece(node);

	}
	else
	{
		if (MarxWorld::getInstance().Volkes != NULL)
			MarxWorld::getInstance().Volkes->DeleteImageControl((ImageControl*)this);
	}
	ObjectNumberingMananger::getInstance()->UnUseNumber(_currentName,this);
}

SelectableObject * SelectableObject::FindSelectTopObj()
{
	if (ObjectMove::getinstance()->SelectObjectNum.size() == 0)
		return NULL;
	return dynamic_cast<SelectableObject*> (
		ObjectNumberingMananger::getInstance()->GetMarxObject(
			ObjectMove::getinstance()->SelectObjectNum[0]));
}


void SelectableObject::setSelect(bool select)
{
	if (m_bselect == select)
		return;
	m_bselect = select;
	old_trance = GetNowPostion();
}

void SelectableObject::Dragging(COMMONDATATYPE::mouse_input_t Mouse)
{
	COMMONDATATYPE::Vector3d obj;
	obj.x = old_trance.x + ((Mouse.x - ObjectMove::getinstance()->old_mouse.x));
	obj.y = old_trance.y + ((Mouse.y - ObjectMove::getinstance()->old_mouse.y));
	obj.z = old_trance.z;
	SetNowPostion(obj);
}


void SelectableObject::setSelectionTopMost()
{
	std::list<SelectableObject*>::reverse_iterator md2begin = child.rbegin();
	std::list<SelectableObject*>::reverse_iterator md2End = child.rend();

	for (; md2begin != md2End; md2begin++)
	{
		SelectableObject* node = ((SelectableObject*)*md2begin);

		if (node->GetUniqNumber() == ObjectMove::getinstance()->SelectObjectNum[0])
		{
			if (child.rbegin() == md2begin)
				return;
			md2begin = 
				std::list<SelectableObject*>::reverse_iterator(
					child.erase((++md2begin).base()));
			child.push_back(node);
			return;
		}
		else
		{
			node->setSelectionTopMost();
		}
	}
}
void SelectableObject::setSelectionTop()
{
	std::list<SelectableObject*>::reverse_iterator md2begin = child.rbegin();
	std::list<SelectableObject*>::reverse_iterator md2End = child.rend();

	for (; md2begin != md2End; md2begin++)
	{
		SelectableObject* node = ((SelectableObject*)*md2begin);
		if (node->GetUniqNumber() == ObjectMove::getinstance()->SelectObjectNum[0])
		{
			if (md2begin == child.rbegin())
				return; // 맨 위면 안해도 되요.

			md2begin = 
				std::list<SelectableObject*>::reverse_iterator(
					child.erase((++md2begin).base()));
			child.insert(md2begin.base(), node);
			return;
		}
		else
		{
			node->setSelectionTop();
		}
	}
}
void SelectableObject::setSelectionBottomMost()
{
	std::list<SelectableObject*>::iterator md2begin = child.begin();
	std::list<SelectableObject*>::iterator md2End = child.end();

	for (; md2begin != md2End; md2begin++)
	{
		SelectableObject* node = ((SelectableObject*)*md2begin);
		if (node->GetUniqNumber() == ObjectMove::getinstance()->SelectObjectNum[0])
		{
			md2begin = child.erase(md2begin);
			child.push_front(node);
			return;
		}
		else
		{
			node->setSelectionBottomMost();
		}
	}

}
void SelectableObject::setSelectionBottom()
{
	std::list<SelectableObject*>::iterator md2begin = child.begin();
	std::list<SelectableObject*>::iterator md2End = child.end();

	for (; md2begin != md2End; md2begin++)
	{
		SelectableObject* node = ((SelectableObject*)*md2begin);
		if (node->GetUniqNumber() == ObjectMove::getinstance()->SelectObjectNum[0])
		{
			if (md2begin == child.begin())
				return; // 맨 밑이면 안해도 되요.

			md2begin = child.erase(md2begin);
			md2begin--;
			child.insert(md2begin, node);
			return;
		}
		else
		{
			node->setSelectionBottom();
		}
	}
}

void SelectableObject::deleteSelectPiece(int _SelectID)
{
	std::list<SelectableObject*>::iterator md2begin = child.begin();
	std::list<SelectableObject*>::iterator md2End = child.end();
	for (; md2begin != md2End; )
	{
		SelectableObject* node = ((SelectableObject*)*md2begin);
		if (node->GetUniqNumber() == _SelectID)
		{
			delete node;
			md2begin = child.erase(md2begin);

			return;
		}
		else
		{
			node->deleteSelectPiece(_SelectID);
		}
		md2begin++;

	}
}

void SelectableObject::Remove(SelectableObject* obj)
{
	list<SelectableObject*>::iterator iter = child.begin();
	while (iter != child.end())
	{
		SelectableObject* contator = (SelectableObject*)*iter;

		if (contator == obj)
		{
			delete contator;
			iter = child.erase(iter);
			return;
		}
		iter++;
	}
}

void SelectableObject::setName(int name)
{
	if (!ObjectNumberingMananger::getInstance()->UseNumber(name,this))
	{
		name = ObjectNumberingMananger::getInstance()->getNumber(this);
		ObjectNumberingMananger::getInstance()->UseNumber(name, this);
	}
	_currentName = name;
}

SelectableObject* SelectableObject::setSelectObj(int number, bool isSelect)
{

	SelectableObject* var1 = FindbyNameObj(number);
	Md2Object* var = dynamic_cast<Md2Object*>(var1);
	
	var1->setSelect(isSelect);
	return var1;
}


SelectableObject* SelectableObject::setSelectObj(int number)
{
	return setSelectObj(number, true);
}

SelectableObject * SelectableObject::FindbyNameObj(int name)
{
	return dynamic_cast<SelectableObject*> (
		ObjectNumberingMananger::getInstance()->GetMarxObject(
			name));
}


void SelectableObject::CopyDeepObj(SelectableObject* obj)
{
	std::list<SelectableObject*>::iterator md2begin = child.begin();
	std::list<SelectableObject*>::iterator md2End = child.end();
	for (; md2begin != md2End; )
	{
		SelectableObject* var = ((SelectableObject*)*md2begin);
		Md2Object* node = dynamic_cast<Md2Object*>(*md2begin);
		if (node != NULL)
		{
			Md2Object* childnode = MarxWorld::getInstance().MakePiece(node);
			obj->child.push_back(childnode);
			var->CopyDeepObj(childnode);
		}
		else if (var->GetType() == MARXOBJECT_TYP_ENUM::MARX_OBJECT_UI)
		{
			ImageControl* cont = (ImageControl*)(*md2begin);
			
			ImageControl* childnode = ImageControl::CreateImageControl(cont);
			obj->child.push_back(childnode);
			var->CopyDeepObj(childnode);
			
		}
		
		md2begin++;

	}
}