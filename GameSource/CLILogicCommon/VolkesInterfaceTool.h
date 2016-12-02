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


	bool SetSelection(Md2Object* model);
	void OneTimeInit();
};


#endif _VOLKESITERFACETOOL_H_