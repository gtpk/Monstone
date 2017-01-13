#ifndef _VOLKESITERFACE_H_
#define _VOLKESITERFACE_H_
 
#include "../Opengl2Md2/ModelInterface.h"
#include "../Opengl2Md2/Md2Object.h"

namespace EXTERN
{
	enum ActionType {
		AddNew,
		Delete,
		Select,
	};
	class Action {
		ActionType Type;
		void* obj;
	};

	class VolkesIterface
	{
	public:
		VolkesIterface(){}

		~VolkesIterface(){}


	public:
		virtual string SaveUrl() = 0;
		virtual void setNewPiece(Md2Object* mother, Md2Object* model) = 0;
		virtual void setNewPiece(Md2Object* model) = 0;
		virtual void DeletePiece(Md2Object* model) = 0;
		virtual bool SetSelection(Md2Object* model) = 0;
		virtual void OneTimeInit() = 0;

	};
}
#endif _VOLKESITERFACE_H_