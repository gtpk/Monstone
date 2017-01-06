#pragma once
#include <random>
#include <string>
#include <vector>
#include <unordered_map>
#include "ImageLoader.h"
#include "AtlasObj.h"
#include "Texture.h"

#include "GL/glew.h"
#include "GL/glut.h"
using namespace std;
using namespace stdext;

class KardNameFactory
{
private:


	vector<string> GameImageNames;
	unordered_map<int, bool> GameResizedImage;// = new hash_map<int, bool>();

	unordered_map<string, int> Image_NameToNummap;// = new hash_map<string, int>();
	ImageLoader* m_loader;

	static KardNameFactory * m_KNF;

	int ImageLoaderCount;

	int LoadingStatus;

	
public:
	GLuint textureName[3];
	bool IsLoaded;

	static bool IsFinishedGame;

	int version;

	unordered_map<string, AtlasObj*> AtlasList;

	bool isOneTimeInit = false;

	enum GameBackground
	{
		NON,
		outGameBackGround,
		InGameBackGround,
		ResualtGameBackGorund,
	};

	GameBackground GameBackgroundType = GameBackground::NON;
	

	KardNameFactory();

	static KardNameFactory* GetKardNameFactory()
	{
		if (m_KNF == NULL)
			m_KNF = new KardNameFactory();
		return m_KNF;
	}
	void SetGameResourceIamge(string _name);


	void SetNextLoadingJob();

	void initBettleStage();

	int score = 0;

	int scoreVictim = 0;

	int GetMyCharScore();

	int GetVictimCharScore();


	int GetLoadingProgress();

	bool IsReadForGame();


	void OneTimeInit();

	void AtlasOpen(int FileName);

	AtlasObj* GetAtlasObj(string Name);

};