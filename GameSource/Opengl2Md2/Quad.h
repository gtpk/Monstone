#pragma once
#define QUADUSE
#ifdef QUADUSE
#include "GL/glew.h"
#include "GL/glut.h"

namespace test {
	class Quad
	{
	public:
		Quad();
		~Quad();
		void draw();
		void InitTexture();
	private:
		int textureName[1] = { 0 };
		unsigned short index[6]{
			0,1,2,
			0,2,3
		};
		int const indexlegnth = 6;
		GLfloat vertexBuffer[15] = {
			0.0f	, 800.0f	, 0.0f, // 0, Left Top
			480.0f	, 800.0f	, 0.0f,	// 1, Right Top
			480.0f	, 0.0f	, 0.0f,	// 2, Right Bottom
			0.0f	, 0.0f	, 0.0f,	// 3, Left Bottom
			0.0f	, 0.0f	, 0.0f,	// 4, Not Use
		};



		float uv_x = 0.46875f;
		float uv_y = 0.78125f;
		GLfloat textureBuffer[10] = {
			0.0f ,uv_y ,
			uv_x , uv_y ,
			uv_x , 0.0f ,
			0.0f, 0.0f  ,
			0.0f, 0.0f  ,
		};
	};

}

#endif