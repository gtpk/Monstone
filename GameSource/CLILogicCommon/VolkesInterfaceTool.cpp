#include "Stdafx.h"
#include "../Common/VolkesInterface.h"
#include "../CLILogicCommon/VolkesInterfaceTool.h"
#include "../Opengl2Md2/ModelInterface.h"
#include "../OpenGLManagedCpp/SelectObjectInterface.h"
#include "../OpenGLManagedCpp/ProjectSettingValuesInterface.h"
#include "../Opengl2Md2/Md2Object.h"
#include "../Opengl2Md2/ProjectLoader.h"
#include "../OpenGLManagedCpp/ObjectTreeContator.h"
#include "../OpenGLManagedCpp/UIObjectTreeContator.h"

using LogicCommon::SelectObjectInterface;
using LogicCommon::ProjectSettingValuesInterface;
using LogicCommon::ObjectTreeContator;
using LogicCommon::UIObjectTreeContator;

VolkesIterfaceTool::VolkesIterfaceTool()
{
}

VolkesIterfaceTool::~VolkesIterfaceTool()
{

}

void VolkesIterfaceTool::setNewPiece(Md2Object* mother, Md2Object* model)
{
	ObjectTreeContator::GetInstance()->setNewPiece(mother,model);
}
void VolkesIterfaceTool::setNewPiece(Md2Object* model)
{
	ObjectTreeContator::GetInstance()->setNewPiece(model);
}

void VolkesIterfaceTool::DeletePiece(Md2Object* model)
{
	SelectObjectInterface^ data = SelectObjectInterface::GetInstance();
	if (data->root == model)
		data->SetMarxObject(NULL);

	ObjectTreeContator::GetInstance()->DeletePiece(model);
}

string VolkesIterfaceTool::SaveUrl()
{
	string sModelname;
	// Displays a SaveFileDialog so the user can save the Image
	// assigned to Button2.
	SaveFileDialog ^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter =
		"xml SetFile|*.xml";
	saveFileDialog1->Title = "Save an Image File";
	saveFileDialog1->ShowDialog();
	String^ selected1 = saveFileDialog1->FileName;

	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(selected1)).ToPointer();
	sModelname = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return sModelname;
}

bool VolkesIterfaceTool::SetMd2ObjectSelection(Md2Object* obj)
{
	SelectObjectInterface^ data = SelectObjectInterface::GetInstance();


	data->SetMarxObject(obj);

	//data->ModelName = gcnew String( model->model()->getMd2name()->c_str() );

	return false;
}

void VolkesIterfaceTool::setNewImageControl(ImageControl* mother, ImageControl* model)
{
	UIObjectTreeContator::GetInstance()->setNewPiece(mother, model);
}
void VolkesIterfaceTool::setNewImageControl(ImageControl* model)
{
	UIObjectTreeContator::GetInstance()->setNewPiece(model);
}

void VolkesIterfaceTool::DeleteImageControl(ImageControl* model)
{
	UIObjectTreeContator^ data = UIObjectTreeContator::GetInstance();
	if (data->root == model)
		data->SetMarxObject(NULL);

	UIObjectTreeContator::GetInstance()->DeletePiece(model);
}
bool VolkesIterfaceTool::SetImageControlSelection(ImageControl* obj)
{
	UIObjectTreeContator^ data = UIObjectTreeContator::GetInstance();


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

void VolkesIterfaceTool::RefreshGameObject()
{
	MarxWorld::getInstance().Refresh();
}