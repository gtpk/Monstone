#include "ObjectMove.h"

ObjectMove* ObjectMove::inst = NULL;
ObjectMove::ObjectMove()
{
}

ObjectMove::~ObjectMove()
{
}

void ObjectMove::OnDraw()
{
	std::list<Md2Object*>::iterator md2begin = MarxWorld::getInstance()._WorldPiece.begin();

	for (; md2begin != MarxWorld::getInstance()._WorldPiece.end(); md2begin++)
	{
		Md2Object* node = (Md2Object*)*md2begin;

		node->SelectDraw();
	}
}