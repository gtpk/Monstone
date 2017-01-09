#include "UIBase.h"
#include "ExGameGraphicInfo.h"

//@Override
void UIBase::SetWidth(float width)
{
	m_Size.x = (int)width;
}

//@Override
void UIBase::SetHeight(float height)
{

	if (m_Size.y == height)
		return;

	if (m_Size.x == 0)
		m_Size.x = getWidth();

	m_Size.y = (int)height;
}

bool UIBase::isPrang(MotionEvent e, int pointCount)
{
	if (visiable == false)
		return false;

	if (isNotClickable == true)
		return false;

	// this.x > evnet.getX >  this.x + getWidth();

	float resolution = ExGameGraphicInfo::GetGameGraphic()->GetResolution();

	if (pointCount >= 2)
	{
		return false;
	}
	Mouse_x = e.x*resolution + ExGameGraphicInfo::GetGameGraphic()->GetBlackScreanSize().x;
	Mouse_y = e.y*resolution + ExGameGraphicInfo::GetGameGraphic()->GetBlackScreanSize().y;

	//minimum_x = x * resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().x;
	//	minimum_y = y * resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().y;

	total_x = getWidth() + x;//(/* minimum_x + */getWidth())*resolution  + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().x;
	total_y = getHeight() + y;//(/* minimum_y + */getHeight())*resolution + ExGameGraphicInfo.GetGameGraphic().GetBlackScreanSize().y;

	minimum_x = x;
	minimum_y = y;

	if (minimum_x < Mouse_x && Mouse_x < total_x &&
		minimum_y < Mouse_y && Mouse_y < total_y)
	{
		return true;
	}

	bool ishorizen = false;

	//Todo :
	//해상도 바뀌면 바꿔야함 상수로 조정예정

	Point GameResolution(480, 800);

	Point TotalSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

	double Resolution = (float)TotalSize.x / (float)GameResolution.x;

	if (GameResolution.y * Resolution < TotalSize.y)
	{
		ishorizen = false;
	}
	else
	{
		ishorizen = true;
		Resolution = (float)TotalSize.y / (float)GameResolution.y;
	}

	int BlackScreanX = 0, BlackScreanY = 0;


	if (ishorizen)
	{
		BlackScreanX = (int)(TotalSize.x - (GameResolution.x * Resolution)) / 2;
	}
	else
	{
		BlackScreanY = (int)(TotalSize.y - (GameResolution.y * Resolution)) / 2;
	}


	return false;
}