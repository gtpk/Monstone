#include "CollisionMap.h"
#include "Texture.h"
#include "triangulate.h"
#include <math.h>
CollisionMap::CollisionMap()
{
}

CollisionMap::~CollisionMap()
{
}

void CollisionMap::onDraw()
{
	onDrawPoint();

	onDrawLine();
}
void CollisionMap::onDrawPoint()
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

void CollisionMap::onDrawLine()
{

	if (dotlist.size() <= 1)
	{
		return;
	}
	glBegin(GL_LINES);
	
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int i = 1; i < dotlist.size(); i++)
		{
			glVertex3f(dotlist[i - 1].x, dotlist[i - 1].y, 0);
			glVertex3f(dotlist[i].x, dotlist[i].y, 0);
		}
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(dotlist[0].x, dotlist[0].y, 0);
		glVertex3f(dotlist[dotlist.size() - 1].x, dotlist[dotlist.size() - 1].y, 0);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);

	if (dotlist.size() <= 2)
	{
		return;
	}

	

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 1.0f, 0.2f, 0.2f);
	for (int i = 0; i < polygonList.size(); i++)
	{

		glVertex3f(dotlist[polygonList[i]].x, dotlist[polygonList[i]].y, 0);
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	for (int i = 0; i < polygonList.size(); i++)
	{

		glVertex3f(dotlist[polygonList[i]].x, dotlist[polygonList[i]].y, 0);
	}
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f,1.0f);
}

void CollisionMap::SetVertext(COMMONDATATYPE::Vector3d dot)
{
	if (isFinish == true)
		return;

	//for (int i = 0; i < dotlist.size(); i++)
	if (dotlist.size() > 3)
	{
		
		float dtx = dotlist[0].x - dot.x;
		float dty = dotlist[0].y - dot.y;

		float length = sqrtf( (dtx*dtx) + (dty * dty));
		if (length < 10)
		{
			isFinish = true;
			polygonList = math::triangulate
				<int, COMMONDATATYPE::Vector3d>
				(dotlist);

			return;
		}
	}
	dotlist.push_back(dot);
}
void CollisionMap::SetVertext(float x, float y)
{
	COMMONDATATYPE::Vector3d dot;
	dot.x = x;
	dot.y = y;
	dot.z = 0;
	dotlist.push_back(dot);
}