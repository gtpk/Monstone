#pragma once
#include "ImageControl.h"
namespace MarxEngine
{

	enum MomoStatus
	{
		Idle,
		Run
	};


	class Momo : public ImageControl
	{
	public:


		long long KingTimer = 0;
		long long  King_targetEndValue = 2;
		long long  King_SpriteValue = 0;

		long long KingRunTimer = 0;
		long long  Momo_targetEndValue = 11;
		long long  Momo_tragetStartValue = 1;
		long long  Momo_spriteValue = 0;

		//private ImageControl King;

	private:

	public:
		bool IsDie = false;

		bool IsEnable = true;


		string KingImage[12];
		string KingRun[12];


		MomoStatus m_KingType;
		void SetType(MomoStatus type)
		{
			if (m_KingType == type)
				return;
			m_KingType = type;
			KingTimer = 0;
			King_SpriteValue = 0;
			KingRunTimer = 0;
			Momo_spriteValue = 1;
		}

		int targetid = 0;
	public:
		Momo() :ImageControl()
		{



			m_KingType = Idle;
			for (int i = 0; i < 4; i++)
			{
				char buff[101];
				snprintf(buff, sizeof(buff), "mb_idle_%02d", i);
				string kingsrc = buff;

				KingImage[i] = kingsrc;
			}
			for (int i =1; i < 12; i++)
			{
				char buff[101];
				snprintf(buff, sizeof(buff), "mb_run_%02d", i);
				string kingsrc = buff;

				KingRun[i] = kingsrc;
			}

			//mb_run_00
			SetType(MomoStatus::Idle);
			setbeckgroundImage(KingImage[0]);
			// TODO Auto-generated constructor stub
		}

		void SetMoveingSpeedDuration(long duration)
		{
			SetAnimationDuration(duration);
		}


	public:



	private:
		long long AnimationDuration = 0;

	public:
		void onUpdate(long long dt)
		{
			if (KingTimer < 0)
				KingTimer = 0;

			if (IsDie == true)
				return;

			if (m_KingType == MomoStatus::Idle)
			{
				KingTimer += dt;

				if (KingTimer > 240)
				{
					if (King_SpriteValue > King_targetEndValue)
						King_SpriteValue = 0;

					setbeckgroundImage(KingImage[King_SpriteValue]);

					King_SpriteValue++;

					KingTimer = 0;
				}
			}
			else
			{
				KingTimer += dt;

				if (KingTimer > 120)
				{
					if (Momo_spriteValue > Momo_targetEndValue)
						Momo_spriteValue = Momo_tragetStartValue;

					setbeckgroundImage(KingRun[Momo_spriteValue]);

					Momo_spriteValue++;

					KingTimer = 0;
				}
			}
			
		}

	};

}