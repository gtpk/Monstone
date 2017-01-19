#include "KardNameFactory.h"
#include "Image.h"
#include "TextureManager.h"
#include <thread>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "MarxWorld.h"
using namespace MarxEngine;

namespace MarxEngine
{
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
			// 텍스쳐 포인터 설정
			// 만약 atlas 늘릴꺼면 textureName 늘려야합니다!
			//glGenTextures(3, textureName);
			isOneTimeInit = true;
		}
		else
			return;

		// Matrix m = new Matrix();
		// m.postScale(-1, 1);  //좌우 반전

		//AssetManager assetManager = ExGameInfo.GetGameInfo().GetContext().getAssets();

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		//  glAlphaFunc(GL_NOTEQUAL, 0);
		//glBlendFunc(GL_SRC_ALPHA,GL_ZERO);

		//glBlendFunc(GL_DST_COLOR, GL_ONE);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);



		bool isfailed = false;
		for (int i = 0; i < 2; i++)
		{
			char buff[100];
			//MarxWorld::getInstance()._RootDirctory
			snprintf(buff, sizeof(buff), "\\asset\\AtlasGen%d.png", i + 1);
			//snprintf(buff, sizeof(buff), "\\Asset\\AtlasGen%d.pcx", i + 1);
			std::string buffAsStdStr = MarxWorld::getInstance()._RootDirctory + buff;
			//TextureManager::Inst()->LoadTexture(buffAsStdStr.c_str(), i+1,GL_RGBA8, GL_RGBA); 
			//!!!! Warnning !!!!
			// 인터레이스가 되어있으면 로딩이 안된다.
			// 압축이 되어있어도 안된다!
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			TextureManager::Inst()->LoadTexture(buffAsStdStr.c_str(), i, GL_BGRA, GL_RGBA8);
			//TextureManager::Inst()->LoadTexture(buffAsStdStr.c_str(), i + 1);
			GLenum err = glGetError();
			printf("Texture Load %s\n", buff);
			if (GL_NO_ERROR != err)
				cerr << "KAD - OpenGL Error: " << gluErrorString(err)
				<< " [Texture::Texture]" << endl;
			AtlasOpen(i);
		}
		//AtlasOpen(4);
		glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		IsLoaded = true;
	}


	void KardNameFactory::AtlasOpen(int FileName)
	{
		char buff[101];
		snprintf(buff, sizeof(buff), "\\Asset\\AtlasGen%d.txt", FileName + 1);
		std::string buffAsStdStr = MarxWorld::getInstance()._RootDirctory + buff;

		FILE* f = fopen(buffAsStdStr.c_str(), "r+");
		char inputString[1001];

		while (fscanf(f, "%s", inputString) != EOF)
		{
			AtlasObj* obj = new AtlasObj();
			string Name(inputString);

			char tempString[1001];
			fscanf(f, "%s", tempString);
			string temp(tempString);

			obj->UV_X = std::stof(temp);
			fscanf(f, "%s", tempString);
			temp = string(tempString);
			obj->UVB_Y = 1 - std::stof(temp);

			fscanf(f, "%s", tempString);
			temp = string(tempString);
			obj->UVB_X = std::stof(temp);
			fscanf(f, "%s", tempString);
			temp = string(tempString);
			obj->UV_Y = 1 - std::stof(temp);

			fscanf(f, "%s", tempString);
			temp = string(tempString);
			obj->Width = std::stof(temp);
			fscanf(f, "%s", tempString);
			temp = string(tempString);
			obj->Height = std::stof(temp);
			//printf("AtlasOpen-> ::|%s|::\n", Name.c_str());
			obj->TextureNum = FileName;
			AtlasList[Name] = obj;
		}
		fclose(f);
		/*
		ifstream outFile(buffAsStdStr);

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
			getline(f, temp, '\n');
			obj->TextureNum = FileName - 1;
			AtlasList[Name] = obj;
			printf("AtlasOpen-> ::|%s|::", Name);
		}
		*/
		//printf("AtlasOpen %d\n", FileName);

	}

	AtlasObj* KardNameFactory::GetAtlasObj(string Name)
	{
		if (AtlasList[Name] == NULL)
			OneTimeInit();
		//printf("Atlasfind %s \n", Name.c_str());
		return AtlasList[Name];
	}
}