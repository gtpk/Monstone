#ifndef _VOLKESITERFACE_H_
#define _VOLKESITERFACE_H_
#include <string>
using namespace std;
class Md2Object;
namespace MarxEngine
{
	class ImageControl;
}

using namespace MarxEngine;

namespace EXTERN
{
	enum ActionType {
		AddNew,
		Delete,
		Select,
	};
	class Action {
		ActionType MARXAnimatnionType;
		void* obj;
	};

	class VolkesIterface
	{
	public:
		VolkesIterface(){}

		~VolkesIterface(){}


	public:
		virtual string SaveUrl() abstract;
		virtual void setNewPiece(Md2Object* mother, Md2Object* model) = 0;
		virtual void setNewPiece(Md2Object* model) = 0;
		virtual void DeletePiece(Md2Object* model) = 0;
		virtual bool SetMd2ObjectSelection(Md2Object* model) = 0;

		virtual void setNewImageControl(ImageControl* mother, ImageControl* model) = 0;
		virtual void setNewImageControl(ImageControl* model) = 0;
		virtual void DeleteImageControl(ImageControl* model) = 0;
		virtual bool SetImageControlSelection(ImageControl* model) = 0;

		virtual void OneTimeInit() = 0;

	};
}
#endif _VOLKESITERFACE_H_