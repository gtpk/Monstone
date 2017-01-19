#pragma once
namespace MarxEngine
{
	class AtlasObj
	{
	public:
		AtlasObj() : UV_X(0), UV_Y(0), UVB_X(0), UVB_Y(0), Width(0), Height(0), TextureNum(0)
		{

		}
		float UV_X;
		float UV_Y;

		float UVB_X;
		float UVB_Y;

		float Width;
		float Height;

		int TextureNum;
	};
}