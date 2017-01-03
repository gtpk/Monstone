#pragma once
#include <random>
#include <string>
#include <vector>
#include <hash_map>
#include "Bitmap.h"
#include "ImageLoader.h"
#include "AtlasObj.h"

#include "GL/glew.h"
#include "GL/glut.h"
using namespace std;
using namespace stdext;

class KardNameFactory
{
private:

	
	//private static MediaPlayer m_Resualt;

	hash_map<int, Bitmap*> GameImageResourece;
	hash_map<int, Bitmap*> GameImageResourece_old;
	vector<int> GameImageNames;
	vector<ImageLoader*> GameImageLoader;
	hash_map<int, bool> GameResizedImage;// = new hash_map<int, bool>();

	hash_map<string, int> Image_NameToNummap;// = new hash_map<string, int>();


	static KardNameFactory * m_KNF;

	int ImageLoaderCount;

	int LoadingStatus;

	GLuint textureName;
public:

	bool IsLoaded;

	static bool IsFinishedGame;

	int version;

	hash_map<string, AtlasObj> AtlasList;

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

	Bitmap* SetDirectGameResourceIamge(string _name, int width, int height)
	{
		return NULL;
	}

	int GetGameResourceNumber(string _name);

	void OneTimeInit();

	void SetNextLoadingJob();

	void initBettleStage();

	int score = 0;

	int scoreVictim = 0;

	int GetMyCharScore();

	int GetVictimCharScore();


	int GetLoadingProgress();

	bool IsReadForGame();

	Bitmap* GetScaledBitmap(int number, bool isMyKard, int width, int height);

	Bitmap* GetScaledBitmapTimeOutGame(int number, int width, int height);

	Bitmap* GetScaledBitmapGame(int number, int width, int height);

	Bitmap* GetScaledBitmapGame(string _string, int width, int height);

	Bitmap* GetScaledBitmapGameForce(string _string, int width, int height);

	void OneTimeInit();

	void AtlasOpen(int FileName);

	AtlasObj GetAtlasObj(string Name);

};