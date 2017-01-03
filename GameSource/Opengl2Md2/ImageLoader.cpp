#include "ImageLoader.h"
#include "KardNameFactory.h"


ImageLoader::ImageLoader(hash_map<int, Bitmap> gameImageResourece,
	vector<int> gameImageNames)
{
	m_ResourseList = gameImageNames;
	m_Count = 0;
	m_MaxCount = gameImageNames.size();
	KARD_output = gameImageResourece;

	oldstyle = false;
	isForceClose = false;
}
ImageLoader::ImageLoader(hash_map<int, Bitmap> gameImageResourece_old, vector<int> gameImageNames)
{
	m_ResourseList = gameImageNames;
	m_Count = 0;
	m_MaxCount = gameImageNames.size();
	KARD_output_old = gameImageResourece_old;

	oldstyle = true;
	isForceClose = false;
}

void ImageLoader::stopThread() 
{
	isForceClose = true;
}

float ImageLoader::GetLoadingPercent() {
	if (m_MaxCount == 0)
		return 1;

	if (m_Count == 0)
		return 0;

	return ((float)(m_Count / m_MaxCount));
}

void ImageLoader::run() {
	while (!isForceClose) {
		if (m_Count < m_MaxCount) {
			BitmapFactory.Options options = new BitmapFactory.Options();
			// Make sure it is 24 bit color as our image processing
			// algorithm expects this format
			options.inPreferredConfig = Config.RGB_565;
			options.inSampleSize = 1;
			//options.inSampleSize = 1;
			// options.inPurgeable = true;
			// options.inJustDecodeBounds = true;
			// 다른 스레드로 리소스를 로드하여 이미지화 시킨다.
			/*
			* BitmapDrawable drawable = (BitmapDrawable)
			* ExGameInfo.GetGameInfo
			* ().GetResource().getDrawable(m_ResourseList.get(m_Count));
			* Bitmap bitmap = drawable.getBitmap();
			* KARD_output.add(bitmap);
			*/

			if (oldstyle == false)
			{

				Bitmap temp = BitmapFactory.decodeResource(ExGameInfo
					.GetGameInfo().GetResource(), m_ResourseList
					.get(m_Count), options);
				if (temp != null)
					KARD_output.put(m_Count, temp);
			}
			else
			{
				options.inSampleSize = 1;

				Bitmap temp = BitmapFactory.decodeResource(ExGameInfo
					.GetGameInfo().GetResource(), m_ResourseList
					.get(m_Count), options);
				if (temp != null)
					KARD_output_old.put(m_Count, temp);
			}


			m_Count++;
			//System.gc();
		}
		else {
			KardNameFactory::GetKardNameFactory()->SetNextLoadingJob();
			return;
		}
	}
}

ImageLoader::~ImageLoader()
{
}
