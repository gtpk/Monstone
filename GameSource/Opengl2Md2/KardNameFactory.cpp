#include "KardNameFactory.h"
#include "Image.h"
#include "TextureManager.h"
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "MarxWorld.h"

bool KardNameFactory::IsFinishedGame = false;
KardNameFactory* KardNameFactory::m_KNF = NULL;
KardNameFactory::KardNameFactory()
{
	m_loader = new ImageLoader();
}

void KardNameFactory::SetGameResourceIamge(string _name)
{
	//Resource Regest
	//Caution! this function does Not Load Immediate!
	GameImageNames.push_back(_name);
}

void KardNameFactory::SetNextLoadingJob()
{
	std::thread([&]()
	{
		m_loader->run();
	}).join();
}

void KardNameFactory::initBettleStage()
{
	score = 0;
	scoreVictim = 0;
}

int KardNameFactory::GetMyCharScore()
{
	return score;
}


int KardNameFactory::GetVictimCharScore()
{
	return scoreVictim;
}

int KardNameFactory::GetLoadingProgress()
{
	return (m_loader->GetLoadingPercent() * 100);
}

bool KardNameFactory::IsReadForGame()
{
	return IsLoaded;
}


void KardNameFactory::OneTimeInit()
{

	if (isOneTimeInit == false)
	{
		// �ؽ��� ������ ����
		// ���� atlas �ø����� textureName �÷����մϴ�!
		//glGenTextures(3, textureName);
		isOneTimeInit = true;
	}

	// Matrix m = new Matrix();
	// m.postScale(-1, 1);  //�¿� ����

	//AssetManager assetManager = ExGameInfo.GetGameInfo().GetContext().getAssets();


	bool isfailed = false;
	for (int i = 0; i <3; i++)
	{
		char buff[100];
		//MarxWorld::getInstance()._RootDirctory
		snprintf(buff, sizeof(buff), "\\asset\\AtlasGen%d.png", i+1);
		std::string buffAsStdStr = MarxWorld::getInstance()._RootDirctory +  buff;
		//String.format("AtlasGen%d.png", i+1)
		//ImageBuffer ibuff(buffAsStdStr);
		//auto_ptr<Image> img(ImageFactory::createImage(ibuff));
		TextureManager::Inst()->LoadTexture(buffAsStdStr.c_str(), i+1,GL_RGBA8,GL_RGBA);
	}
	AtlasOpen(1);
	AtlasOpen(2);
	AtlasOpen(3);
	//AtlasOpen(4);


	IsLoaded = true;
}


void KardNameFactory::AtlasOpen(int FileName)
{
	char buff[101];
	snprintf(buff, sizeof(buff), "\\asset\\AtlasGen%d.txt", FileName);
	std::string buffAsStdStr = MarxWorld::getInstance()._RootDirctory + buff;

	FILE* f = fopen(buffAsStdStr.c_str(), "r+");
	char inputString[1001];
	
	while (fscanf(f, "%s", inputString) == 2)
	{
		AtlasObj* obj = new AtlasObj();
		string Name(inputString);

		char tempString[1001];
		fscanf(f, "%s", tempString);
		string temp(tempString);

		obj->UV_X = std::stof(temp);
		fscanf(f, "%s", tempString);
		temp = string(tempString);
		obj->UV_Y = std::stof(temp);

		fscanf(f, "%s", tempString);
		temp = string(tempString);
		obj->UVB_X = std::stof(temp);
		fscanf(f, "%s", tempString);
		temp = string(tempString);
		obj->UVB_Y = std::stof(temp);

		fscanf(f, "%s", tempString);
		temp = string(tempString);
		obj->Width = std::stof(temp);
		fscanf(f, "%s", tempString);
		temp = string(tempString);
		obj->Height = std::stof(temp);
	}
	/*
	ifstream outFile(buffAsStdStr);
	
	while (!outFile.eof())
	{ //���پ� �б�
		outFile.getline(inputString, 1000);

		istringstream f(inputString);
		

		AtlasObj* obj = new AtlasObj();
		string Name;
		getline(f, Name, ' ');

		string temp;
		getline(f, temp, ' ');
		obj->UV_X = std::stof(temp);
		getline(f, temp, ' ');
		obj->UV_Y = std::stof(temp);

		getline(f, temp, ' ');
		obj->UVB_X = std::stof(temp);
		getline(f, temp, ' ');
		obj->UVB_Y = std::stof(temp);

		getline(f, temp, ' ');
		obj->Width = std::stof(temp);
		getline(f, temp, ' ');
		obj->Height = std::stof(temp);
		getline(f, temp, '\n');
		obj->TextureNum = FileName - 1;
		AtlasList[Name] = obj;
		printf("AtlasOpen-> ::|%s|::", Name);
	}
	*/
	printf("AtlasOpen %d", FileName);

}

AtlasObj* KardNameFactory::GetAtlasObj(string Name)
{
	return AtlasList[Name];
}