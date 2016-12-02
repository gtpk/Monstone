#ifndef _VOLKESITERFACE_H_
#define _VOLKESITERFACE_H_
 
#include "../Opengl2Md2/ModelInterface.h"
#include "../Opengl2Md2/Md2Object.h"

namespace EXTERN
{
	class VolkesIterface
	{
	public:
		VolkesIterface(){}

		~VolkesIterface(){}


	public:


		virtual bool SetSelection(Md2Object* model) = 0;
		virtual void OneTimeInit() = 0;

	};
}
#endif _VOLKESITERFACE_H_