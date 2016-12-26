#include "ProjectLoader.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "MarxWorld.h"
#include <string>

ProjectLoader* ProjectLoader::instance = NULL;
ProjectLoader::ProjectLoader() : isLoaded(false)
{

}

ProjectLoader::~ProjectLoader()
{
}

ProjectLoader* ProjectLoader::getinstance()
{
	if (ProjectLoader::instance == NULL)
		ProjectLoader::instance = new ProjectLoader();
	return ProjectLoader::instance;
}

string ProjectLoader::GetProjectPath()
{

	if(isLoaded == false)
		LoadProjectFile("ProjectProperty.xml");

	return ProjectPath;
}

string ProjectLoader::GetProjectPath(string path)
{

	if(isLoaded == false)
		LoadProjectFile(path);

	return ProjectPath;
}



bool ProjectLoader::LoadProjectFile(string path)
{

	isLoaded = true;

	TiXmlDocument doc( path.c_str() );
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		// 파일이 없음..!!
		return false;
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
	}

	TiXmlNode* root = doc.FirstChild();

	TiXmlDeclaration* declar = (TiXmlDeclaration*)root;
	if (declar != NULL)
	{

		if (strcmp(declar->Version(), "1.0") != 0)
		{
			// 버전이 일치 하지 않음
			return false;
		}
	}

	TiXmlNode* MapNode;
	MapNode = doc.FirstChild("Project");

	TiXmlElement* MinMonstersMap = MapNode->ToElement();
	ProjectPath = MinMonstersMap->Attribute("RootFolder");

	return true;

}

void ProjectLoader::SaveProjectFile()
{

	TiXmlDocument doc;  
	TiXmlElement* msg;

	//문서 설정
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	
	doc.LinkEndChild( decl );
	// Root 만들자
	TiXmlElement * root = new TiXmlElement( "Project" );  
	doc.LinkEndChild( root ); 

	root->SetAttribute("RootFolder",ProjectPath.c_str());
	
	doc.SaveFile("ProjectProperty.xml");
}