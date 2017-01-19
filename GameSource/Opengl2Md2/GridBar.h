#pragma once
namespace MarxEngine
{
	enum GridBarType
	{
		Horizontal,
		Vertical
	};

	class GridBar
	{
	public:
		GridBarType MARXAnimatnionType;
		float Value;

		GridBar(float _value, GridBarType _type)
		{
			Value = _value;
			MARXAnimatnionType = _type;
		}

	};
}