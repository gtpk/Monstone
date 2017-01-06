#include "Animation.h"
#include "defAnimations.h"

void Animation::Copy(Animation _ani)
{
	mStartValue = _ani.mStartValue;
	mEndValue = _ani.mEndValue;
	mDuration = _ani.mDuration;
	mSaveStartTime = _ani.mSaveStartTime;
	mFinish = _ani.mFinish;
	mRepeat = _ani.mRepeat;
	m_AniType = _ani.m_AniType;
}

float Animation::easeFunction(float t, float b, float c, float d)
{
	switch (m_AniType) {
	case QuintEaseIn:
		return Quint::easeIn(t, b, c, d);
	case QuintEaseOut:
		return Quint::easeOut(t, b, c, d);
	case QuintEaseInOut:
		return Quint::easeInOut(t, b, c, d);
	case QuartEaseIn:
		return Quart::easeIn(t, b, c, d);
	case QuartEaseOut:
		return Quart::easeOut(t, b, c, d);
	case QuartEaseInOut:
		return Quart::easeInOut(t, b, c, d);
	case QuadEaseIn:
		return Quart::easeIn(t, b, c, d);
	case QuadEaseOut:
		return Quart::easeOut(t, b, c, d);
	case QuadEaseInOut:
		return Quart::easeInOut(t, b, c, d);
	case LinearEaseIn:
		return Linear::easeIn(t, b, c, d);
	case LinearEaseOut:
		return Linear::easeNone(t, b, c, d);
	case LinearEaseInOut:
		return Linear::easeNone(t, b, c, d);
	case ExpoEaseIn:
		return Expo::easeIn(t, b, c, d);
	case ExpoEaseOut:
		return Expo::easeOut(t, b, c, d);
	case ExpoEaseInOut:
		return Expo::easeInOut(t, b, c, d);
	case ElasticEaseIn:
		return Elastic::easeIn(t, b, c, d);
	case ElasticEaseOut:
		return Elastic::easeOut(t, b, c, d);
	case ElasticEaseInOut:
		return Elastic::easeInOut(t, b, c, d);
	case CubicEaseIn:
		return Cubic::easeIn(t, b, c, d);
	case CubicEaseOut:
		return Cubic::easeOut(t, b, c, d);
	case CubicEaseInOut:
		return Cubic::easeInOut(t, b, c, d);
	case BackEaseIn:
		return Back::easeIn(t, b, c, d);
	case BackEaseOut:
		return Back::easeOut(t, b, c, d);
	case BackEaseInOut:
		return Back::easeInOut(t, b, c, d);
	case BounceEaseIn:
		return Bounce::easeIn(t, b, c, d);
	case BounceEaseOut:
		return Bounce::easeOut(t, b, c, d);
	case BounceEaseInOut:
		return Bounce::easeInOut(t, b, c, d);
	case CircEaseIn:
		return Circ::easeIn(t, b, c, d);
	case CircEaseOut:
		return Circ::easeOut(t, b, c, d);
	case CircEaseInOut:
		return Circ::easeInOut(t, b, c, d);

	case LinearleaseNone:
		return Linear::easeNone(t, b, c, d);
	default:
		return Linear::easeNone(t, b, c, d);
	}
}

Animation::Animation(Type type) {
	mType = type;
	m_AniType = AnimationType::LinearleaseNone;
}



bool Animation::isStarted() {

	milliseconds ms = duration_cast< milliseconds >(system_clock::now()- mSaveStartTime);

	if (ms.count() >= mDuration) {
		return true;
	}
	return false;
}

bool Animation::isEnded()
{
	if (isRepeat() == true)
	{
		return false;
	}
	return mFinish;
}

bool Animation::isRepeat() {
	return mRepeat;
}


float Animation::getCurrentValue(long long currentTime) {

	if (isPause == true)
	{
		PauseSaved = currentTime;
		return currentValue;
	}

	if (mDelay != 0)
	{
		if (currentTime < mDelay)
		{
			return mStartValue;
		}
		else if (currentTime > mDelay)
		{
			mSaveStartTime = system_clock::now();
			mDelay = 0;
			return mStartValue;
		}
	}




	/*
	if(currentTime >= mStartTime + mDuration )
	return mEndValue;
	*/
	if (isEnded() == true)
		return mEndValue;


	currentValue =
		easeFunction(
			currentTime,
			mStartValue,
			mEndValue - mStartValue,
			mDuration);


	/*
	= mStartValue + (currentTime)
	* (mEndValue - mStartValue) / mDuration;
	*/

	if (currentTime >= mDuration)
	{
		if (isRepeat() == true)
		{
			Play();
		}
		else
		{
			currentValue = mEndValue;
			Stop();
		}

	}

	return currentValue;
}

void Animation::Play()
{
	if (isPause == true)
	{
		//TODO
		long long duration = system_clock::now().time_since_epoch().count() + PauseSaved;

		std::chrono::milliseconds dur(duration);
		std::chrono::time_point<std::chrono::system_clock> dt(dur);
		mSaveStartTime = dt;
	}
	else
	{
		mSaveStartTime = system_clock::now();
	}

	mFinish = false;
}

void Animation::Pause()
{
	isPause = true;
	PauseSaved = 0;
}

void Animation::Stop()
{
	mFinish = true;
}