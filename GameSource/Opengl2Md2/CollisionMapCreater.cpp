#include "CollisionMapCreater.h"
#include "Texture.h"
CollisionMapCreater* CollisionMapCreater::inst = NULL;
CollisionMapCreater::CollisionMapCreater()
{
}

CollisionMapCreater::~CollisionMapCreater()
{
}

void CollisionMapCreater::onDraw()
{
	
	std::vector<CollisionMap*>::iterator _itor = dotlist.begin();
	for (int i =0 ; i < dotlist.size(); i++)
	{
		glPushName(i);
		dotlist[i]->onDraw();
		glPopName();
	}
}
void CollisionMapCreater::NewCollisionMap()
{
	CollisionMap* newnode = new CollisionMap();
	dotlist.push_back(newnode);
	selectNumber = dotlist.size() - 1;
}
void CollisionMapCreater::SelectPoint(float x, float y)
{
	
}
void CollisionMapCreater::SetVertext(COMMONDATATYPE::Vector3d dot)
{
	if (selectNumber == -1)
	{
		NewCollisionMap();
	}
	dotlist[selectNumber]->SetVertext(dot);
}
void CollisionMapCreater::SetVertext(float x, float y)
{
	COMMONDATATYPE::Vector3d dot;
	dot.x = x;
	dot.y = y;
	dot.z = 0;
	SetVertext(dot);
}