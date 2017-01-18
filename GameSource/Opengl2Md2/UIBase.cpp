#include "UIBase.h"
#include "ExGameGraphicInfo.h"

//@Override
void UIBase::SetWidth(float width)
{
	m_Size.x = (int)width;

	float vertices[] = {
		0.0f	, m_Size.y	, 0.0f, // 0, Left Top
		m_Size.x	, m_Size.y	, 0.0f,	// 1, Right Top
		m_Size.x	, 0.0f	, 0.0f,	// 2, Right Bottom
		0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
	};
}

//@Override
void UIBase::SetHeight(float height)
{

	if (m_Size.y == height)
		return;

	if (m_Size.x == 0)
		m_Size.x = getWidth();

	m_Size.y = (int)height;

	float vertices[] = {
		0.0f	, m_Size.y	, 0.0f, // 0, Left Top
		m_Size.x	, m_Size.y	, 0.0f,	// 1, Right Top
		m_Size.x	, 0.0f	, 0.0f,	// 2, Right Bottom
		0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
	};
}

bool UIBase::isPrang(MotionEvent e, int pointCount)
{
	if (visiable == false)
		return false;

	if (isNotClickable == true)
		return false;

	Mouse_x = e.x;
	Mouse_y = e.y;


	total_x = getWidth() + x;//(/* minimum_x + */getWidth())*resolution  + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().x;
	total_y = getHeight() + y;//(/* minimum_y + */getHeight())*resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().y;

	minimum_x = x;
	minimum_y = y;

	if (minimum_x < Mouse_x && Mouse_x < total_x &&
		minimum_y < Mouse_y && Mouse_y < total_y)
	{
		return true;
	}

	return false;
}