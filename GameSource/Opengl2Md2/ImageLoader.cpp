#include "ImageLoader.h"
#include "KardNameFactory.h"
#include "TextureManager.h"
using namespace MarxEngine;
namespace MarxEngine
{
	ImageLoader::ImageLoader()
	{

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
				Texture2DManager *texMgr = Texture2DManager::getInstance();
				m_Count++;
			}
		}
	}

}