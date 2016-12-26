#include "../Externallib/tinyxml_2_6_2/tinyxml/tinyxml.h"
#include <string>
#include "stdio.h"


void SaveProjectFile()
{

	TiXmlDocument doc;
	TiXmlElement* msg;

	//���� ����
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");

	doc.LinkEndChild(decl);
	// Root ������
	TiXmlElement * root = new TiXmlElement("Project");
	doc.LinkEndChild(root);

	root->SetAttribute("RootFolder", "testproject");

	doc.SaveFile("ProjectProperty.xml");
}

int main()
{

	SaveProjectFile();

	TiXmlDocument doc("ProjectProperty.xml");
	bool loadOkay = doc.LoadFile();

	if (!loadOkay)
	{
		// ������ ����..!!
		return false;
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
	}

	TiXmlNode* root = doc.FirstChild();

	TiXmlDeclaration* declar = (TiXmlDeclaration*)root;
	if (declar != NULL)
	{

		if (strcmp(declar->Version(), "1.0") != 0)
		{
			// ������ ��ġ ���� ����
			return false;
		}
	}

	TiXmlNode* MapNode;
	MapNode = doc.FirstChild("Project");

	TiXmlElement* MinMonstersMap = MapNode->ToElement();
	const char* teststring = MinMonstersMap->Attribute("RootFolder");
	printf("%s\n", teststring);
}
