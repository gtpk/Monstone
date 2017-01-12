#pragma once
#include "IRootUI.h"
#include <vector>
#include "Penal.h"
#include <string>

using namespace std;

class RootUI : IRootUI 
{
private :
	vector<IEventHandler<ClickEventArgs>*> TouchEvent;

public :
	static Point GameSize;

private :
	vector<Penal*> m_Child;

public :
	RootUI()
	{
		GameSize = ExGameGraphicInfo::GetGameGraphic()->GetGameSize();

	}

public :
	void addChild(Penal* child)
	{
		m_Child.push_back(child);
	}

public :
	void addEventHandler(IEventHandler<ClickEventArgs>* handler)
	{
		TouchEvent.push_back(handler);
	}

public :
	void onTouchEvent(MotionEvent event)
	{
		ImageControl* targetImage = NULL;

		vector<Penal*>::iterator iter = m_Child.begin();

		//buttons[GLUT_LEFT_BUTTON] == GLUT_UP
		while (iter != m_Child.end()) {
			Penal* ParentControl = *iter;

			int action = event.state;

			int PointNum = 0;

			//if (MotionEvent.ACTION_POINTER_UP == (action & MotionEvent.ACTION_MASK)
			//	|| MotionEvent.ACTION_POINTER_DOWN == (action & MotionEvent.ACTION_MASK)) {
			//	// Extract the index of the pointer that left the touch sensor
			//	final int pointerIndex = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
			//	PointNum = event.getPointerId(pointerIndex);
			//
			//}

			// for(int i=0;i<event.getPointerCount();++i)
			{
				if (ParentControl->isPrang(event, PointNum)) {
					targetImage = ParentControl;
				}

				vector<IContainer*> TempList = ParentControl->getAllChild();

				// Penal에서 Icontainer를 가져오는 경우 하나 밖에 없으므로 하나만 가져온다.
				IContainer* tempContanier = TempList[0];

				// 모든 리스트 가져온다.
				//tempContanier->getAllChild();

				vector<ImageControl*> child = tempContanier->getAllChild();

				vector<ImageControl*>::iterator iter_container = child.begin();
				while (iter_container != child.end())
				{
					ImageControl* DrawableControl = *iter_container;

					if (DrawableControl->isPrang(event, PointNum)) {
						targetImage = DrawableControl;
					}
				}

				if (targetImage != NULL) {

					vector<IEventHandler<ClickEventArgs>* >::iterator eventitor = TouchEvent.begin();
					while (eventitor != TouchEvent.end())
					{
						(*eventitor)->eventReceived(targetImage, ClickEventArgs(event));
					}
					
				}
			}
		}
	}

public :
	ImageControl* CreateImageControl(Penal* target, string objectName,
		string ImageName, int x, int y, int width, int height)
	{
		ImageControl* _ImageControl = new ImageControl(ImageName, width, height);
		_ImageControl->x = x;
		_ImageControl->y = y;
		_ImageControl->Name = objectName;
		target->addChile(_ImageControl);
		return _ImageControl;
	}

public :
	ImageControl* CreateImageControl(Penal* target, string objectName,
		string ImageName, int x, int y)
	{
		ImageControl* _ImageControl = new ImageControl(ImageName);
		_ImageControl->x = x;
		_ImageControl->y = y;
		_ImageControl->Name = objectName;
		target->addChile(_ImageControl);
		return _ImageControl;
	}

public :
	void OnCreate()
	{
		// TODO Auto-generated method stub

	}

public :

public :
	void OnTouch(UIBase* sender, ClickEventArgs e)
	{

	}

public:
	void OnShow()
	{
		// TODO Auto-generated method stub

	}

public:
	void onClose()
	{
		// TODO Auto-generated method stub
		/*
		Iterator<Penal> iter_penal = m_Child.iterator();

		while (iter_penal.hasNext())
		{
		Penal ParentControl = iter_penal.next();
		LinkedList<IContainer> Child = ParentControl.getAllChild();
		Iterator<IContainer> iter_Child = Child.iterator();

		while (iter_Child.hasNext())
		{
		IContainer DrawableControl = iter_Child.next();
		DrawableControl.AllAnimationFinished();
		}
		}
		*/

	}

public:
	void onUpdate(long long dt)
	{
		// TODO Auto-generated method stub

	}

public :
	void OnDraw() 
	{
		vector<Penal*>::iterator iter = m_Child.begin();

		while (iter != m_Child.end()) {
			Penal* ParentControl = *iter;

			vector<IContainer*> TempList = ParentControl->getAllChild();
			vector<IContainer*>::iterator tempitor = TempList.begin();
			while (tempitor != TempList.end()) 
			{
				IContainer* DrawableControl = *tempitor;
				DrawableControl->OnDraw();
			}
		}
	}

};
