#include "Stdafx.h"
#include "../Common/VolkesInterface.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "../Opengl2Md2/ModelInterface.h"
#include "../OpenGLManagedCpp/SelectObjectInterface.h"
#include "../OpenGLManagedCpp/ProjectSettingValuesInterface.h"
#include "../Opengl2Md2/Md2Object.h"
#include "../Opengl2Md2/ProjectLoader.h"

using LogicCommon::SelectObjectInterface;
using LogicCommon::ProjectSettingValuesInterface;

VolkesIterfaceTool::VolkesIterfaceTool()
{
}

VolkesIterfaceTool::~VolkesIterfaceTool()
{

}

bool VolkesIterfaceTool::SetSelection(Md2Object* obj)
{
	SelectObjectInterface^ data = SelectObjectInterface::GetInstance();

	data->CurrentName = obj->getName();

	data->ModelName = gcnew String( obj->model()->getMd2name().c_str() );

	data->TextureName = gcnew String( obj->model()->getTextureName().c_str() );

	data->AlphaTextureName = gcnew String( obj->model()->getAlphaTextureName().c_str() );

	data->Scale = obj->model()->getScale();

	data->Width = obj->model()->GetPieceWidth();

	data->Height = obj->model()->GetPieceHeight();

	data->Rotation = gcnew Vector3D(obj->getRotate()[0] ,
									obj->getRotate()[1] ,
									obj->getRotate()[2]);

	data->Trance = gcnew Vector3D(  obj->getTranslate()[0] ,
									obj->getTranslate()[1] ,
									obj->getTranslate()[2]);

	//data->ModelName = gcnew String( model->model()->getMd2name()->c_str() );

	return false;
}

void VolkesIterfaceTool::OneTimeInit()
{
	ProjectSettingValuesInterface^ data = ProjectSettingValuesInterface::GetInstance();

	string path2 = ProjectLoader::getinstance().GetProjectPath();

	data->ProjectPath =  gcnew String(path2.c_str());

}