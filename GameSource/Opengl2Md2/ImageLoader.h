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

class ImageLoader
{

private:
	bool isForceClose = false;
	vector<int> m_ResourseList;
	int m_Count;
	int m_MaxCount;
	hash_map<int, Bitmap> KARD_output;

	hash_map<int, Bitmap> KARD_output_old;

	bool oldstyle = false;

public:
	ImageLoader(hash_map<int, Bitmap> gameImageResourece,vector<int> gameImageNames);

	ImageLoader(hash_map<int, Bitmap> gameImageResourece_old, vector<int> gameImageNames);

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

