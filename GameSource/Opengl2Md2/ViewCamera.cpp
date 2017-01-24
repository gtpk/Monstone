#include "ViewCamera.h"

ViewCamera* ViewCamera::inst = NULL;

ViewCamera::ViewCamera()
{
	eye.x = 0.0f;
	eye.y = 0.0f;
	eye.z = 0.0f;
}

ViewCamera::~ViewCamera()
{

}

