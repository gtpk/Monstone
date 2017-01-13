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

	void setNewPiece(Md2Object* mother, Md2Object* model);
	void setNewPiece(Md2Object* model);
	void DeletePiece(Md2Object* model);
	bool SetSelection(Md2Object* model);


	string SaveUrl();
	void OneTimeInit();
};


#endif _VOLKESITERFACETOOL_H_