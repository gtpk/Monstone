#pragma once
#include "ImageControl.h"
#include "IContainer.h"
#include "UIBase.h"
#include <vector>
#include "GridBar.h"
#include "AnimatinonBase.h"
#include <algorithm>
using namespace std;
class Grid : public ImageControl , IContainer
{

public :
	bool isusegrid;
	

public :
	

	vector<float> m_gridbar_hor;
	vector<float> m_gridbar_ver;

private :
	vector<ImageControl*> m_Child;
	Point GridSize;

public :
	vector<ImageControl*> getAll_Child;
	bool IsChanged = false;

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


public :
	void addChild(ImageControl* child)
	{
		IsChanged = true;
		m_Child.push_back(child);
	}

public:

	virtual void eventReceived(UIBase* sender, ClickEventArgs e) { }



public :
	vector<ImageControl*> getAllChild()
	{

		if (IsChanged == true)
		{
			IsChanged = false;
			getAll_Child.clear();

			//getAll_Child = new vector<ImageControl>();
			vector<ImageControl*>::iterator iter = m_Child.begin();
			while (iter != m_Child.end())
			{
				ImageControl* contator = (ImageControl*)*iter;
				IContainer* _IContainer = dynamic_cast<IContainer*>(contator);
				if (_IContainer != NULL)
				{
					vector<ImageControl*> coninside = _IContainer->getAllChild();
					vector<ImageControl*>::iterator iter2 = coninside.begin();
					while (iter2 != coninside.end())
					{
						getAll_Child.push_back((ImageControl*)*iter2);
						iter2++;
					}
				}
				else if (dynamic_cast<ImageControl*>(contator) != NULL)
				{
					getAll_Child.push_back((ImageControl*)contator);
				}
				else
				{
					iter++;
				}
			}
		}

		return getAll_Child;
	}


	void OnDraw() 
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
		}
		itor++;
	}





public :
	// Note! ����Ʈ������ ��������. ��ü�� ������ �ʴ´�!
	void Remove(ImageControl* child)
	{
		vector<ImageControl*>::iterator iter = m_Child.begin();
		while (iter != m_Child.end())
		{
			ImageControl* contator = (ImageControl*)*iter;

			if (contator == child)
			{
				iter = m_Child.erase(iter);
				return;
			}
			iter++;	
		}
	}

public :
	bool AllAnimationFinished()
	{
	
		vector<ImageControl*>::iterator iter = m_Child.begin();
		while (iter != m_Child.end())
		{
			ImageControl* GridControl = (ImageControl*)*iter;
			if (GridControl->AnimationisEnded() == false)
				return false;
		}

		return true;

	}


};