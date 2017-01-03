#include "KardNameFactory.h"
#include "Texture.h"
#include "Image.h"
#include "TextureManager.h"
#include <thread>

bool KardNameFactory::IsFinishedGame = false;

void KardNameFactory::SetGameResourceIamge(string _name)
{

	// Get texture manager
	Texture2DManager *texMgr = Texture2DManager::getInstance();
	// load the texture
	Texture2D *tex = texMgr->load(_name);
	Image_NameToNummap[_name] = GameImageNames.size() - 1;
}

int KardNameFactory::GetGameResourceNumber(string _name)
{
	if (Image_NameToNummap.find(_name) == Image_NameToNummap.end())
		return -1;
	return Image_NameToNummap[_name];
}


void KardNameFactory::OneTimeInit()
{
	if (IsLoaded == true)
		return;

	if (version > 11)
	{
		GameImageLoader.push_back(new ImageLoader(GameImageResourece, GameImageNames));
		ImageLoaderCount++;
	}
	else
	{
		GameImageLoader.push_back(new ImageLoader(GameImageResourece_old, GameImageNames));
		ImageLoaderCount++;
	}

	IsLoaded = true;

	// 이미지 로딩 시작

	SetNextLoadingJob();
}

void KardNameFactory::SetNextLoadingJob()
{
	if (LoadingStatus < ImageLoaderCount)
	{
		std::thread(GameImageLoader[LoadingStatus]).join();
		LoadingStatus++;
	}
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
	float Total = 0;
	for (int i = 0; i < ImageLoaderCount; i++)
	{
		Total += (float)((float)GameImageLoader[i]->GetLoadingPercent()*((float)100 / (float)ImageLoaderCount));
	}

	int reualt = (int)Total;
	if (reualt % 2 == 1)
		reualt += 1;

	return reualt;
}

bool KardNameFactory::IsReadForGame()
{
	return IsLoaded;
}

Bitmap* KardNameFactory::GetScaledBitmap(int number, bool isMyKard, int width, int height)
{
	return NULL;
}

Bitmap* KardNameFactory::GetScaledBitmapTimeOutGame(int number, int width, int height)
{
	return NULL;
}

Bitmap* KardNameFactory::GetScaledBitmapGame(int number, int width, int height)
{
	if (IsLoaded == false)
		return NULL;

	if (number < 0)
		return NULL;

	if (number >= GameImageNames.size())
		return NULL;

	return Bitmap.createScaledBitmap(GameImageResourece.get(number), width, height, true);

}

Bitmap* KardNameFactory::GetScaledBitmapGame(string _string, int width, int height)
{
	int number = GetGameResourceNumber(_string);

	if (IsLoaded == false)
		return NULL;

	if (number == -1)
	{
		if (version > 11)
		{
			return SetDirectGameResourceIamge(_string, width, height);
		}
		else
		{
			return SetDirectGameResourceIamge(_string, width, height);
		}

	}
	else
	{
		if (version > 11)
		{
			Bitmap* test = GameImageResourece.get(number);
			if (test == NULL)
				return NULL;


			if (GameResizedImage.find(number) != GameResizedImage.end())
			{
				return  GameImageResourece[number];
			}
			else
			{
				Bitmap* Resizing = Bitmap.createScaledBitmap(test, width, height, true);
				GameResizedImage[number] = true;
				GameImageResourece[number]= Resizing;
				return Resizing;
			}

		}
		else
		{
			Bitmap*  test = GameImageResourece_old[number];
			if (test == NULL)
				return NULL;

			if (GameResizedImage.find(number) != GameResizedImage.end())
			{
				return  GameImageResourece_old[number];
			}
			else
			{
				Bitmap* Resizing = Bitmap.createScaledBitmap(test, width, height, true);
				GameResizedImage[number]= true;
				GameImageResourece_old[number] =Resizing;
				return Resizing;
			}

		}

	}
}

Bitmap* KardNameFactory::GetScaledBitmapGameForce(string _string, int width, int height)
{
	int number = GetGameResourceNumber(_string);


	if (IsLoaded == false)
		return NULL;

	if (number == -1)
	{

		if (version > 11)
		{
			return SetDirectGameResourceIamge(_string, width, height);
		}
		else
		{
			return SetDirectGameResourceIamge(_string, width, height);
		}

	}
	else
	{
		if (version > 11)
		{
			Bitmap*  test = GameImageResourece[number];
			if (test == NULL)
				return NULL;

			Bitmap* Resizing = Bitmap.createScaledBitmap(test, width, height, true);
			return Resizing;

		}
		else
		{
			Bitmap*  test = GameImageResourece_old[number];
			if (test == NULL)
				return NULL;

			Bitmap* Resizing = Bitmap.createScaledBitmap(test, width, height, true);
			return Resizing;
		}

	}


}


void KardNameFactory::OneTimeInit()
{

	if (isOneTimeInit == false)
	{
		// 텍스쳐 포인터 설정
		glGenTextures(3, &textureName);
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

		if (isfailed == true)
		{
			imgPanda = BitmapFactory.decodeFile(string.format("file:///android_asset/AtlasGen%d.png", i + 1));
			isfailed = false;
		}
		else
		{
			imgPanda = BitmapFactory.decodeStream(istr);
		}

		if (imgPanda != NULL)
		{
			//Bitmap imgPanda = BitmapFactory.decodeResource(ExGameInfo.GetGameInfo().GetContext().getResources(),Number);

			glBindTexture( GL_TEXTURE_2D, textureName[i]);	// 텍스쳐 사용 연결

			glTexParameterf( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER,  GL_NEAREST);
			// glTexParameterf( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER,  GL_LINEAR);


			GLUtils.texImage2D( GL_TEXTURE_2D, 0, imgPanda, 0);

			imgPanda.recycle();
			imgPanda = NULL;
		}
		else
		{
			isfailed = true;
			i--;

		}
		istr = NULL;
	}
	AtlasOpen(1);
	AtlasOpen(2);
	AtlasOpen(3);
	//AtlasOpen(4);


	IsLoaded = true;
}


void KardNameFactory::AtlasOpen(int FileName)
{
	string line;
	BufferedReader r;
	InputStream in = ExGameInfo.GetGameInfo().GetContext().getAssets().open(string.format("AtlasGen%d.txt", FileName));
	r = new BufferedReader(new InputStreamReader(in));

	while ((line = r.readLine()) != NULL)
	{ //한줄씩 읽기

		stringTokenizer token = new stringTokenizer(line, " ");

		AtlasObj obj;// = new AtlasObj();
		string Name = token.nextToken(); //값을 저장하기
		obj.UV_X = std::stof(token.nextToken());
		obj.UV_Y = std::stof(token.nextToken());

		obj.UVB_X = std::stof(token.nextToken());
		obj.UVB_Y = std::stof(token.nextToken());

		obj.Width = std::stof(token.nextToken());
		obj.Height = std::stof(token.nextToken());

		obj.TextureNum = FileName - 1;
		AtlasList[Name] = obj;

		printf("AtlasOpen %s", Name);
	}


}

AtlasObj KardNameFactory::GetAtlasObj(string Name)
{
	return AtlasList[Name];
}