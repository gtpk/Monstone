#include <FTGL/ftgl.h>
#include <FTFont.h>
#include "TinyFont.h"
#include <stdio.h>
#include <Windows.h>
#include "GL/glew.h"
#include "ExGameGraphicInfo.h"
#include <string>
using namespace MarxEngine;

TinyFont::TinyFont(int size, int type, const char * fontfile)
{
	m_font = NULL;
	switch (type)
	{
	case FONT_OUTLINE:
		m_font = new FTGLOutlineFont(fontfile);
		break;
	case FONT_POLYGON:
		m_font = new FTGLPolygonFont(fontfile);
		break;
	case FONT_TEXTURE:
		m_font = new FTGLTextureFont(fontfile);
		break;
	case FONT_PIXEL:
		m_font = new FTGLPixmapFont(fontfile);
		break;
	case FONT_BITMAP:
		m_font = new FTGLBitmapFont(fontfile);
		break;
	case FONT_EXTRD:
		m_font = new FTGLExtrdFont(fontfile);
		break;

	}

	m_type = type;
	if (!m_font)
	{
		//	fprintf( stderr, "Failed to open font %s", fontfile);
		//	exit(1);
		MessageBox(NULL, "지정된 폰트가 없습니다.", "ERROR", MB_OK);
	}

	if (!m_font->FaceSize(size))
	{
		//	fprintf( stderr, "Failed to set size");
		//	exit(1);
		MessageBox(NULL, "폰트 사이즈를 변경할수 없습니다.", "ERROR", MB_OK);
	}

	m_font->Depth(100);

	m_font->CharMap(ft_encoding_unicode);

	m_Size = DEFAULT_SIZE;
}

TinyFont::~TinyFont()
{
	if (m_font != NULL)
	{
		delete m_font;
		m_font = NULL;
	}
}

std::string s;



void TinyFont::Print(float x, float y, float z, float r, float g, float b, float a, int type, const char * __data, ...)
{

	if (m_font == NULL)return;

	va_list marker;
	va_start(marker, __data);
	s = format_arg_list(__data, marker);
	va_end(marker);
	if (s.size() == 0)
		return;

	Point size =  ExGameGraphicInfo::GetGameGraphic()->m_GameSize;

	switch (type)
	{
	case FONT_SCREEN:


		if (m_type == FONT_POLYGON)
		{
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
		}
		glDisable(GL_BLEND);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, size.x, 0, size.y, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glNormal3f(0.0, 0.0, 1.0);
		glTranslated(x, size.y - y - m_Size, 0);
		glColor4f(r, g, b, a);
		m_font->Render(s.c_str());

		glColor4f(1, 1, 1, 1);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);

		break;
	case FONT_VIEWPORT:
		if (m_type == FONT_POLYGON)
		{
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
		}

		glDisable(GL_BLEND);

		glPushMatrix();
		glNormal3f(0.0, 0.0, 1.0);
		glTranslated(x, y, z);
		glColor4f(r, g, b, a);

		m_font->Render(s.c_str());
		glColor4f(1, 1, 1, 1);
		glPopMatrix();
		break;
	}
}
WCHAR lpszBuffer[1000];
void TinyFont::Print(float x, float y, float z, float r, float g, float b, float a, int type, WCHAR  * __data, ...)
{

	if (m_font == NULL)return;

	va_list marker;
	va_start(marker, __data);
	vswprintf(lpszBuffer, __data, marker);
	va_end(marker);

	if (lpszBuffer[0] == NULL)
		return;
	
	Point size = ExGameGraphicInfo::GetGameGraphic()->m_GameSize;

	switch (type)
	{
	case FONT_SCREEN:


		if (m_type == FONT_POLYGON)
		{
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
		}
		glDisable(GL_BLEND);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, size.x, 0, size.y, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glNormal3f(0.0, 0.0, 1.0);
		glTranslated(x, size.y - y - m_Size, 0);
		glColor4f(r, g, b, a);
		m_font->Render(lpszBuffer);

		glColor4f(1, 1, 1, 1);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_DEPTH_TEST);

		break;
	case FONT_VIEWPORT:
		if (m_type == FONT_POLYGON)
		{
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
		}

		glDisable(GL_BLEND);

		glPushMatrix();
		glNormal3f(0.0, 0.0, 1.0);
		glTranslated(x, y, z);
		glColor4f(r, g, b, a);

		m_font->Render(lpszBuffer);
		glColor4f(1, 1, 1, 1);
		glPopMatrix();
		break;
	}
}