#pragma once
#include <chrono>
using namespace std::chrono;

namespace MarxEngine
{
	enum MARXAnimatnionType {
		TranslateX, TranslateY,
		PositionX, PositionY, Alpha, ScaleX, ScaleY, ScaleXY, Rotate,
	};

	enum AnimationType
	{
		LinearleaseNone,
		BackEaseIn,
		BackEaseOut,
		BackEaseInOut,

		BounceEaseIn,
		BounceEaseOut,
		BounceEaseInOut,

		CircEaseIn,
		CircEaseOut,
		CircEaseInOut,

		CubicEaseIn,
		CubicEaseOut,
		CubicEaseInOut,

		ElasticEaseIn,
		ElasticEaseOut,
		ElasticEaseInOut,

		ExpoEaseIn,
		ExpoEaseOut,
		ExpoEaseInOut,

		LinearEaseIn,
		LinearEaseOut,
		LinearEaseInOut,

		QuadEaseIn,
		QuadEaseOut,
		QuadEaseInOut,

		QuartEaseIn,
		QuartEaseOut,
		QuartEaseInOut,

		QuintEaseIn,
		QuintEaseOut,
		QuintEaseInOut,
	};


	class Animation 
	{
	public :

		Animation()
		{
		}

	
		float mStartValue;
		float mEndValue;
		long long mDuration = 0;
		long long mDelay = 0;
		long long mSaveStartTime;
		bool mFinish = false;
		bool mRepeat = false;
		MARXAnimatnionType mType;
		bool isPause = false;
		AnimationType m_AniType;


		void Copy(Animation _ani);

		float easeFunction(float t, float b, float c, float d);

		Animation(MARXAnimatnionType type);



		bool isStarted();

		bool isEnded();

		bool isRepeat();


		long long PauseSaved = 0;

		float currentValue = 0;
		float getCurrentValue(long long currentTime);
		void Play();
		void Pause();

		void Stop();
	};


}