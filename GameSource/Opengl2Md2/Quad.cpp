#include "Quad.h"

Quad::Quad()
{

}

void Quad::draw()
{


	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();
	glTranslatef(240, 400, 0);
	glDrawElements(GL_TRIANGLE_STRIP, indexlegnth, GL_UNSIGNED_SHORT, index);
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void Quad::InitTexture()
{
	Resources res = ExGameInfo.GetGameInfo().GetResource();
	String packName = ExGameInfo.GetGameInfo().getPackageName();

	int Number = res.getIdentifier("atlasgen1", "drawable", packName);
	//								atlasgen1.png


	Bitmap imgPanda = BitmapFactory.decodeResource(context.getResources(), Number);


	glGenTextures(1, textureName, 0);					// 텍스쳐 포인터 설정
	glBindTexture(GL_TEXTURE_2D, textureName[0]);	// 텍스쳐 사용 연결

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLUtils.texImage2D(GL_TEXTURE_2D, 0, imgPanda, 0);

	imgPanda.recycle();
}

Quad::~Quad()
{
}