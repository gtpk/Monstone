#ifndef GLGAMERENDERER_H
#define GLGAMERENDERER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdlib.h>

static const char mVertexShader[] = "attribute vec4 mPosition;\n"
	"void main() \n"
	"{\n"
	" gl_Position = mPosition;\n"
	"}\n";

static const char mFragmentShader[] = "precision mediump float; \n"
	"void main()	\n"
	"{	\n"
	" gl_FragColor = vec4(0.63671875, 0.76953125, 0.22265625, 1.0); \n"
	"} \n";

void onSurfaceCreate();

void onSurfaceChanged(int width, int height);

void updateGameLoop();

void onTouchEvent(int x, int y, int touchFlag);

GLuint createProgram(const char* vertex, const char* fragment);

GLuint loadShader(GLuint type, const char* source);

#endif
