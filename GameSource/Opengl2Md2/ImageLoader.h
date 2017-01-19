#pragma once

#include <random>
#include <string>
#include <vector>
#include <unordered_map>
#include "ImageLoader.h"
#include "AtlasObj.h"

#include "GL/glew.h"
#include "GL/glut.h"

using namespace std;
using namespace stdext;
namespace MarxEngine
{
	class ImageLoader
	{

	private:
		bool isForceClose = false;
		vector<int> m_ResourseList;
		int m_Count;
		int m_MaxCount;

		bool oldstyle = false;

	public:
		ImageLoader();

		void stopThread();
		/*
		public Bitmap[] GetBitmapRsualt() {
		if (m_Count >= m_MaxCount) {
		return KARD_output.toArray(new Bitmap[KARD_output.size()]);
		} else {
		return null;
		}
		}*/

		float GetLoadingPercent();
		void run();
	};

}