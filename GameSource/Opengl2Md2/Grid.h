#pragma once
#include "ImageControl.h"
#include "IContainer.h"
#include "UIBase.h"
#include <vector>
#include "GridBar.h"
#include "AnimatinonBase.h"
#include <algorithm>
using namespace std;
class Grid : public ImageControl
{

public :
	bool isusegrid;
	

public :
	

	vector<float> m_gridbar_hor;
	vector<float> m_gridbar_ver;

private :
	Point GridSize;


public :
	Grid()
	{
		GridSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();
		isusegrid = false;
	}

public :
	void addBar(GridBar bar)
	{
		if (bar.Type == GridBarType::Horizontal)
		{
			m_gridbar_hor.push_back(bar.Value);
			sort(m_gridbar_hor.begin(), m_gridbar_hor.end());
		}
		else
		{
			m_gridbar_ver.push_back(bar.Value);
			sort(m_gridbar_ver.begin(), m_gridbar_ver.end());
		}
	}




public:

	virtual void eventReceived(UIBase* sender, ClickEventArgs e) { }

public :
	


	void OnDraw(bool isSelect = false)
	{
		vector<ImageControl*> child = getAllChild();
		vector<ImageControl*>::iterator itor = child.begin();

		while (itor != child.end())
		{

			ImageControl* GridControl = (ImageControl*)*itor;

			if (isusegrid == true && GridControl->x == 0 && GridControl->y == 0)
			{
				Point GridNumber(GridControl->getGridNum().x, GridControl->getGridNum().y);
				Point MargeNumber(GridControl->getGridSize().x, GridControl->getGridSize().y);

				if (GridNumber.x + 1 > m_gridbar_hor.size() || GridNumber.x < 0)
				{
					//������ �߸��Ǹ� 0;
					GridNumber.x = 0;
				}

				if (GridNumber.y + 1 > m_gridbar_ver.size() || GridNumber.y < 0)
				{
					//������ �߸��Ǿ������� 0
					GridNumber.y = 0;
				}

				// ���� ����� ������
				GridNumber.x -= 1;
				GridNumber.y -= 1;

				//����� ��ƺ���
				int Carculate_width = 0;
				int Carculate_hegiht = 0;

				//ǥ �ø��Ⱑ ���̰� ������ ������ ����


				// �Ѿ�� ȭ������ �־�����.
				if (GridNumber.x + MargeNumber.x + 1 >= m_gridbar_hor.size())
				{
					if (GridNumber.x == -1)
					{
						Carculate_width = (int)(GridSize.x);
					}
					else
					{
						Carculate_width = (int)(GridSize.x - m_gridbar_hor[GridNumber.x]);
					}
				}
				else
				{
					if (GridNumber.x == -1)
					{
						Carculate_width = (int)(m_gridbar_hor[GridNumber.x + MargeNumber.x + 1]
							+ 0);
					}
					else
					{
						Carculate_width = (int)(m_gridbar_hor[GridNumber.x + MargeNumber.x + 1]
							- m_gridbar_hor[GridNumber.x]);
					}
				}

				//���� �߸��Ǹ� ������ 0�̴�.				
				if (GridNumber.y + MargeNumber.y + 1 >= m_gridbar_ver.size())
				{
					//GridNumber.y = GameSize.y;
					if (GridNumber.y == -1)
					{
						Carculate_hegiht = (int)(GridSize.y);
					}
					else
					{
						Carculate_hegiht = (int)(GridSize.y - m_gridbar_ver[GridNumber.y]);
					}
				}
				else
				{
					if (GridNumber.y == -1)
					{
						Carculate_hegiht = (int)(m_gridbar_ver[GridNumber.y + MargeNumber.y + 1]
							+ 0);
					}
					else
					{
						Carculate_hegiht = (int)(m_gridbar_ver[GridNumber.y + MargeNumber.y + 1]
							- m_gridbar_ver[GridNumber.y]);
					}
				}

				if (Carculate_hegiht != 0 && Carculate_width != 0)
				{
					GridControl->SetWidth(Carculate_width);
					GridControl->SetHeight(Carculate_hegiht);
				}

				Point PositionNumber;
				if (GridNumber.x == -1)
					PositionNumber.x = 0;
				else
					PositionNumber.x = (int)(m_gridbar_hor[GridNumber.x] + 0);

				if (GridNumber.y == -1)
					PositionNumber.y = 0;
				else
					PositionNumber.y = (int)(m_gridbar_ver[GridNumber.y] + 0);

				GridControl->SetActualX(PositionNumber.x);
				GridControl->SetActualY(PositionNumber.y);

				if (GridControl->visiable == true)
					GridControl->OnDraw();
			}
			else
			{
				if (GridControl->visiable == true)
				{
					GridControl->OnDraw();
				}
			}
			itor++;
		}
		
	}






};