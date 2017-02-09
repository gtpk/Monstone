#pragma once
#include <list>

#include "MarxObject.h"
class SelectableObject;

struct EdgeTarget
{
	SelectableObject *obj;
	int id;
	int direction;
};

class SelectableObject : public MarxObject
{
public:
	SelectableObject();
	~SelectableObject();


	void setSelect(bool select);
	bool getSelect() { return m_bselect; }

	void setSelectionTopMost();
	void setSelectionTop();
	void setSelectionBottomMost();
	void setSelectionBottom();
	void deleteSelectPiece(int _SelectID);
	void Remove(SelectableObject* obj);

	SelectableObject * FindSelectTopObj();

	SelectableObject* setSelectObj(int number, bool isSelect);
	SelectableObject* setSelectObj(int number);
	SelectableObject* FindbyNameObj(int name);

	void CopyDeepObj(SelectableObject* obj);

	int GetUniqNumber() { return _currentName; }
	
	void setName(int name);


	std::list<SelectableObject*> child;

protected:
	EdgeTarget slelectList[8];

	
	int _currentName;
	bool m_bselect;
	
	int SelectNumbers[9] = { 0 ,};
	
};
