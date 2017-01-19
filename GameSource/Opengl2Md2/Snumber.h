#pragma once
#include "ImageControl.h"
namespace MarxEngine
{
	enum Align
	{
		Left,
		Right,
		Middle,
	};

	class Snumber : public ImageControl
	{


	private:
		int m_number = 0;
	public:
		void setNumber(int Num)
		{
			m_number = Num;

			char buff[101];
			snprintf(buff, sizeof(buff), "%d", Num);
			std::string buffAsStdStr = buff;

			setTotalNumberlength(buffAsStdStr.length());
		}

	private:
		int m_NumberCount = 10;
	public:
		void setTotalNumberlength(int length)
		{
			m_NumberCount = length;

			int Commacount = m_NumberCount / 3;
			this->SetWidth(((m_NumberCount + 1) * 24) + Commacount * 12);
			NumberSize();
		}

	public:
		Align TextAlign = Align::Left;

	public:
		ImageControl NumberImage[10];
	public:
		ImageControl CommaImage; //가로가 12인듯

	private:
		int NumberSizeWidth = 24;
	private:
		int NumberSizeHight = 28;

	private:
		int NumberSizeCommaWidth = 17;

	private:
		int NumberActureSize = 0;

	public:
		Snumber()
		{

			for (int i = 0; i < 10; i++)
			{
				char buff[101];
				snprintf(buff, sizeof(buff), "score_%02d", i);
				std::string buffAsStdStr = buff;

				NumberImage[i] = ImageControl(buffAsStdStr, NumberSizeWidth, NumberSizeHight);
			}
			CommaImage = ImageControl("score_comma", NumberSizeWidth, NumberSizeHight);

			this->SetHeight(30);
		}

	public:
		Snumber(int NumberSizeW, int NumberSizeH)
		{
			//super(KardNameFactory.GetKardNameFactory().GetScaledBitmapGame("score_00", 64,64) );

			NumberSizeWidth = NumberSizeW;
			NumberSizeHight = NumberSizeH;
			NumberSizeCommaWidth = NumberSizeW / 2;


			for (int i = 0; i < 10; i++)
			{
				char buff[101];
				snprintf(buff, sizeof(buff), "score_%02d", i);
				std::string buffAsStdStr = buff;

				NumberImage[i] = ImageControl(buffAsStdStr, NumberSizeWidth, NumberSizeHight);
			}
			CommaImage = ImageControl("score_comma", NumberSizeWidth, NumberSizeHight);

			this->SetHeight(30);
		}




	public:
		void AnimationRemoveAll()
		{
			// TODO Auto-generated method stub
			for (int i = 0; i < 10; i++)
				NumberImage[i].AnimationRemoveAll();
		}

		void SetAnimation(Animation* _ani)
		{
			// TODO Auto-generated method stub
			//super.SetAnimation(_ani);
			for (int i = 0; i < 10; i++)
				NumberImage[i].SetAnimation(_ani);
			CommaImage.SetAnimation(_ani);
		}

		void OnDraw()
		{
			if (visiable == false)
				return;
			// 나 자신을 그림을 그리지 않는다.
			//ImageControl::OnDraw();

			//요기에서 숫자 그리자!

			//string To int And Find out Number count
			OnNumberDraw(m_number, m_NumberCount);
		}

	private:
		void OnNumberDraw(int LeftNumber, int LeftCount)
		{
			if (LeftCount <= 0)
				return;

			int CurrentNumber = LeftNumber % 10;

			int NowPosition = LeftCount - m_NumberCount;

			int Commacount = NowPosition / 3;

			float XPosition = 0;/*x + (LeftCount * NumberSizeWidth) + Commacount*NumberSizeCommaWidth*/;
			float YPosition = y;

			if (TextAlign == Align::Left)
			{
				XPosition = x + (LeftCount * NumberSizeWidth) + Commacount*NumberSizeCommaWidth;
			}
			else if (TextAlign == Align::Middle)
			{
				XPosition = x + (LeftCount * NumberSizeWidth) + Commacount*NumberSizeCommaWidth + ((getNumberWidth() - NumberActureSize) / 2);
			}
			else if (TextAlign == Align::Right)
			{
				XPosition = x + getNumberWidth() + (NowPosition * NumberSizeWidth) + Commacount*NumberSizeCommaWidth;
			}


			if (NowPosition < -2)
			{
				if ((int)(NowPosition % 3) == 0)
				{
					CommaImage.x = XPosition + NumberSizeWidth;
					CommaImage.y = YPosition;
					CommaImage.OnDraw();
					//cv.drawBitmap(CommaImage, ,YPosition, paint);
				}
			}

			NumberImage[CurrentNumber].x = XPosition;
			NumberImage[CurrentNumber].y = YPosition;
			NumberImage[CurrentNumber].OnDraw();

			//cv.drawBitmap(NumberImage[CurrentNumber], XPosition ,YPosition, paint);
			OnNumberDraw(LeftNumber / 10, --LeftCount);
		}

	private:
		int NumberSize()
		{
			int Commacount = m_NumberCount / 3;
			int XPosition = (m_NumberCount * NumberSizeWidth) + Commacount*NumberSizeCommaWidth;
			NumberActureSize = XPosition;
			return NumberActureSize;
		}

	private:
		int m_Width = 0;

	public:
		void SetNumberWidth(int Width) {
			m_Width = Width;
		}

	public:
		int getNumberWidth()
		{
			return m_Width;
		}
	};
}