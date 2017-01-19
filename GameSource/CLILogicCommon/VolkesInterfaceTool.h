#ifndef _VOLKESITERFACETOOL_H_
#define _VOLKESITERFACETOOL_H_
 
#include "../Opengl2Md2/ModelInterface.h"
#include "../Opengl2Md2/Md2Object.h"
#include "../Common/VolkesInterface.h"

class VolkesIterfaceTool : EXTERN::VolkesIterface
{
public:
	VolkesIterfaceTool();
	~VolkesIterfaceTool();

	string SaveUrl();
	void setNewPiece(Md2Object* mother, Md2Object* model);
	void setNewPiece(Md2Object* model);
	void DeletePiece(Md2Object* model);
	bool SetMd2ObjectSelection(Md2Object* model);

	void setNewImageControl(ImageControl* mother, ImageControl* model);
	void setNewImageControl(ImageControl* model);
	void DeleteImageControl(ImageControl* model);
	bool SetImageControlSelection(ImageControl* model);

	
	void OneTimeInit();
};


#endif _VOLKESITERFACETOOL_H_