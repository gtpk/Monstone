#include "ProjectLoader.h"
#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include "Md2Player.h"
#include <string>


ProjectLoader::ProjectLoader() : isLoaded(false)
{

}

ProjectLoader::~ProjectLoader()
{
}

ProjectLoader& ProjectLoader::getinstance()
{
	static ProjectLoader instance;
	return instance;
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

	if ( !loadOkay )
	{
		// ������ ����..!!
		return false;
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
	}


	TiXmlDeclaration* declar = doc.ToDeclaration();
	if(declar != NULL)
	{
		if(declar->Version() != "1.0")
		{
			// ������ ��ġ ���� ����
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

	//���� ����
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	
	doc.LinkEndChild( decl );
	// Root ������
	TiXmlElement * root = new TiXmlElement( "Project" );  
	doc.LinkEndChild( root ); 

	root->SetAttribute("RootFolder",Md2Player::getInstance()._RootDirctory.c_str());
	
	doc.SaveFile("ProjectProperty.xml");
}