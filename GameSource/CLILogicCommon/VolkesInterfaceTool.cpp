#include "Stdafx.h"
#include "../Common/VolkesInterface.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "../Opengl2Md2/ModelInterface.h"
#include "../OpenGLManagedCpp/SelectObjectInterface.h"
#include "../OpenGLManagedCpp/ProjectSettingValuesInterface.h"
#include "../Opengl2Md2/Md2Object.h"
#include "../Opengl2Md2/ProjectLoader.h"
#include "../OpenGLManagedCpp/ObjectTreeContator.h"

using LogicCommon::SelectObjectInterface;
using LogicCommon::ProjectSettingValuesInterface;
using LogicCommon::ObjectTreeContator;

VolkesIterfaceTool::VolkesIterfaceTool()
{
}

VolkesIterfaceTool::~VolkesIterfaceTool()
{

}

void VolkesIterfaceTool::setNewPiece(Md2Object* model)
{
	ObjectTreeContator::GetInstance()->setNewPiece(model);
}

bool VolkesIterfaceTool::SetSelection(Md2Object* obj)
{
	SelectObjectInterface^ data = SelectObjectInterface::GetInstance();

	data->SetMarxObject(obj);

	//data->ModelName = gcnew String( model->model()->getMd2name()->c_str() );

	return false;
}

void VolkesIterfaceTool::OneTimeInit()
{
	ProjectSettingValuesInterface^ data = ProjectSettingValuesInterface::GetInstance();

	string path2 = ProjectLoader::getinstance()->GetProjectPath();

	data->ProjectPath =  gcnew String(path2.c_str());

}