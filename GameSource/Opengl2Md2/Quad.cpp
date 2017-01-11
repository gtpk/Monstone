#include "Quad.h"
#include "TextureManager.h"

#ifdef QUADUSE

using namespace test;

Quad::Quad()
{

}

void Quad::draw()
{

	
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_ALPHA_TEST);


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glPushMatrix();

	glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
	//
	glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);
	//glTranslatef(10, 10, 0);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	TextureManager::Inst()->BindTexture(1);
	glDrawElements(GL_TRIANGLES, indexlegnth, GL_UNSIGNED_SHORT, index);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
void Quad::InitTexture()
{

	//glBindTexture(GL_TEXTURE_2D, textureName[0]);	// 텍스쳐 사용 연결

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

Quad::~Quad()
{
}
#endif