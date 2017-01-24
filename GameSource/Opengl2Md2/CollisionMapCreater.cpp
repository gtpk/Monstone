#include "CollisionMapCreater.h"
#include "Texture.h"
CollisionMapCreater* CollisionMapCreater::inst = NULL;
CollisionMapCreater::CollisionMapCreater()
{
	COMMONDATATYPE::Vector3d test;
	test.x = 200; test.y = 200; test.z = 0;
	dotlist.push_back(test);
	test.x = 100; test.y = 100; test.z = 0;
	dotlist.push_back(test);
	test.x = 100; test.y = 0; test.z = 0;
	dotlist.push_back(test);
}

CollisionMapCreater::~CollisionMapCreater()
{
}

void CollisionMapCreater::onDraw()
{
	onDrawPoint();

	onDrawLine();
}
void CollisionMapCreater::onDrawPoint()
{
	float x1 = 5;
	float y1 = 5;
	float x2 = (-1 * 5);
	float y2 = (-1 * 5);

	std::vector<COMMONDATATYPE::Vector3d>::iterator _itor = dotlist.begin();
	for (; _itor != dotlist.end(); _itor++)
	{
		COMMONDATATYPE::Vector3d node = *_itor;
		glPushMatrix();
		glTranslatef(node.x, node.y, node.z);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);

			glVertex3f(x2, y2, 0);
			glVertex3f(x2, y1, 0);
			glVertex3f(x1, y2, 0);
			glVertex3f(x1, y1, 0);
		glEnd();
		glPopMatrix();
	}
}

void CollisionMapCreater::onDrawLine()
{
	
	if (dotlist.size() <= 1)
	{
		return;
	}
	glBegin(GL_LINES);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int i = 1; i < dotlist.size(); i++)
		{
			glVertex3f(dotlist[i-1].x, dotlist[i-1].y,0);
			glVertex3f(dotlist[i].x, dotlist[i].y,0);
		}

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(dotlist[0].x, dotlist[0].y, 0);
		glVertex3f(dotlist[dotlist.size()-1].x, dotlist[dotlist.size()-1].y, 0);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
}

void CollisionMapCreater::SetVertext(COMMONDATATYPE::Vector3d dot)
{
	dotlist.push_back(dot);
}
void CollisionMapCreater::SetVertext(float x, float y)
{
	COMMONDATATYPE::Vector3d dot;
	dot.x = x;
	dot.y = y;
	dot.z = 0;
	dotlist.push_back(dot);
}