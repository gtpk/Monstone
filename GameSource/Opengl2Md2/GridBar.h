#pragma once

enum GridBarType
{
	Horizontal,
	Vertical
};

class GridBar
{
public:
	GridBarType Type;
	float Value;

	GridBar(float _value, GridBarType _type)
	{
		Value = _value;
		Type = _type;
	}

};
