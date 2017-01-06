#include "KardNameFactory.h"
#include "Image.h"
#include "TextureManager.h"
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>


bool KardNameFactory::IsFinishedGame = false;

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
		// 텍스쳐 포인터 설정
		// 만약 atlas 늘릴꺼면 textureName 늘려야합니다!
		glGenTextures(3, textureName);
		isOneTimeInit = true;
	}

	// Matrix m = new Matrix();
	// m.postScale(-1, 1);  //좌우 반전

	//AssetManager assetManager = ExGameInfo.GetGameInfo().GetContext().getAssets();


	bool isfailed = false;
	for (int i = 0; i <3; i++)
	{
		char buff[100];
		snprintf(buff, sizeof(buff), "AtlasGen%d.png", i+1);
		std::string buffAsStdStr = buff;
		//String.format("AtlasGen%d.png", i+1)
		ImageBuffer ibuff(buffAsStdStr);
		auto_ptr<Image> img(ImageFactory::createImage(ibuff));
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
	snprintf(buff, sizeof(buff), "AtlasGen%d.txt", FileName);
	ifstream outFile(buff);
	char inputString[1001];
	while (!outFile.eof())
	{ //한줄씩 읽기
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

		obj->TextureNum = FileName - 1;
		AtlasList[Name] = obj;
		printf("AtlasOpen-> ::|%s|::", Name);
	}
	printf("AtlasOpen %s", FileName);

}

AtlasObj* KardNameFactory::GetAtlasObj(string Name)
{
	return AtlasList[Name];
}