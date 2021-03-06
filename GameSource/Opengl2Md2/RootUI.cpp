#include "Penal.h"
#include "RootUI.h"
using namespace MarxEngine;
namespace MarxEngine
{
	RootUI::RootUI()
	{
		Penal();
	}

	void RootUI::addEventHandler(IEventHandler<ClickEventArgs>* handler)
	{
		TouchEvent.push_back(handler);
	}

	void RootUI::onTouchEvent(MotionEvent event)
	{
		ImageControl* targetImage = NULL;
		vector<ImageControl*> cc = m_Container->getAllChild();
		vector<ImageControl*>::iterator iter = cc.begin();

		//buttons[GLUT_LEFT_BUTTON] == GLUT_UP
		while (iter != cc.end()) {
			ImageControl* ParentControl = *iter;

			int action = event.state;

			int PointNum = 0;

			if (ParentControl->isPrang(event, PointNum)) {
				targetImage = ParentControl;
			}

			if (targetImage != NULL) {

				vector<IEventHandler<ClickEventArgs>* >::iterator eventitor = TouchEvent.begin();
				while (eventitor != TouchEvent.end())
				{
					(*eventitor)->eventReceived(targetImage, ClickEventArgs(event));
					eventitor++;
				}
				return;
			}

			iter++;
		}
	}
}