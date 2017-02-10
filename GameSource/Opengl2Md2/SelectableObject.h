#pragma once
#include <list>

#include "MarxObject.h"
#include "CommonDataType.h"
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

	virtual COMMONDATATYPE::Vector3d GetNowPostion() = 0;
	virtual void SetNowPostion(COMMONDATATYPE::Vector3d pos) = 0;

	SelectableObject* setSelectObj(int number);
	SelectableObject* FindbyNameObj(int name);

	void CopyDeepObj(SelectableObject* obj);

	int GetUniqNumber() { return _currentName; }
	
	void setName(int name);
	void Dragging(COMMONDATATYPE::mouse_input_t);

	std::list<SelectableObject*> child;

protected:
	EdgeTarget slelectList[8];
	COMMONDATATYPE::Vector3d	old_trance;
	
	int _currentName;
	bool m_bselect;
	
	int SelectNumbers[9] = { 0 ,};
	
};
