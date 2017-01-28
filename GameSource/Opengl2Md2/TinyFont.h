#pragma once

#ifdef WIN32
#define FONT_FILE "H2porl.ttf"

#endif
#ifndef FONT_H
#define FONT_H
#define FONT_SCREEN   5 
#define FONT_VIEWPORT 6


#define FONT_OUTLINE 0
#define FONT_POLYGON 1
#define FONT_TEXTURE 2
#define FONT_PIXEL   3
#define FONT_BITMAP  4
#define FONT_EXTRD   5



#define DEFAULT_SIZE 20
#include <FTGL/ftgl.h>


#include <FTGLExtrdFont.h>
#include <FTGLOutlineFont.h>
#include <FTGLPolygonFont.h>
#include <FTGLTextureFont.h>
#include <FTGLPixmapFont.h>
#include <FTGLBitmapFont.h>
#include <string>
#include <Windows.h>

class TinyFont
{
public:

	FTFont* m_font;
	int     m_Size;
	int     m_type;


	~TinyFont();
	TinyFont(int size = 20, int type = FONT_TEXTURE, const char * fontfile = FONT_FILE);
	std::string TinyFont::format_arg_list(const char *fmt, va_list args)
	{
		if (!fmt) return "";
		int   result = -1, length = 1024;
		char *buffer = 0;
		while (result == -1) {
			if (buffer)
				delete[] buffer;
			buffer = new char[length + 1];
			memset(buffer, 0, length + 1);

			// remove deprecate warning
			//result = _vsnprintf(buffer, length, fmt, args);

			result = _vsnprintf_s(buffer, length, _TRUNCATE, fmt, args);
			length *= 2;
		}
		std::string s(buffer);
		delete[] buffer;
		return s;
	}

	void Print(float x, float y, float z, float r, float g, float b, float a, int type, const char * _data, ...);
	void Print(float x, float y, float z, float r, float g, float b, float a, int type, WCHAR  * _data, ...);
};
#endif