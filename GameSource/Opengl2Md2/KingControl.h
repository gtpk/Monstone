#pragma once
#include "ImageControl.h"
namespace MarxEngine
{
	enum KingType
	{
		NormarKing,
		HammerKing,
		CrazyKing,
		TwistKng,
	};


	enum KingStatus
	{
		Down,
		Cheas,
		Score,
		Animation_1,
		Animation_2,
	};


	class KingControl : public ImageControl
	{
	public:


		long long KingTimer = 0;
		long long  King_targetEndValue = 4;
		long long  King_SpriteValue = 0;

		//private ImageControl King;

	private:

	public:
		bool IsDie = false;

		bool IsEnable = true;


		string KingImage[12];

		string KingEyeImage;

		KingType m_KingType;

		int targetid = 0;
	public:
		KingControl() :ImageControl()
		{



			m_KingType = NormarKing;
			string FolderName;
			{
				char buff[101];
				snprintf(buff, sizeof(buff), "king_big/", targetid);
				FolderName = buff;
			}
			for (int i = 0; i < 4; i++)
			{
				char buff[101];
				snprintf(buff, sizeof(buff), "king_under_%02d", i);
				string kingsrc = buff;

				KingImage[i] = kingsrc;
			}

			KingEyeImage = "eyes_01";
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

			KingTimer += dt;

			if (KingTimer > 120)
			{
				if (King_SpriteValue > King_targetEndValue)
					King_SpriteValue = 0;

				setbeckgroundImage(KingImage[King_SpriteValue]);

				King_SpriteValue++;

				KingTimer = 0;
			}
		}

	};
}