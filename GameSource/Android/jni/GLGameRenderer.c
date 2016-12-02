#include "GLGameRenderer.h"

const GLfloat square[] = {
        -0.5, 0.5, 0.0,            // Top left
        -0.5, -0.5, 0.0,           // Bottom left
        0.5, -0.5, 0.0,            // Bottom right
        0.5, 0.5, 0.0              // Top right
    };

GLuint mProgram = -1;
GLuint mPositionHandle = -1;

void onSurfaceCreate()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	mProgram = createProgram(mVertexShader, mFragmentShader);

	if (mProgram == 0) // fail create program!
	{
		return;
	}

	mPositionHandle = glGetAttribLocation(mProgram, "mPosition");
}

void onSurfaceChanged(int width, int height)
{
	glViewport(0, 0, width, height);
}

void updateGameLoop()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/** draw **/
	glUseProgram(mProgram);

	glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, square);
	glEnableVertexAttribArray(mPositionHandle);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}

void onTouchEvent(int x, int y, int touchFlag)
{
}

GLuint createProgram(const char* vertex, const char* fragment)
{
	GLuint program = 0;

	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertex);
	if (vertexShader == 0) // Error load vertex shader
	{
		return 0;
	}
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER,fragment);
	if (fragmentShader == 0) // Error load fragment shader
	{
		return 0;
	}

	program = glCreateProgram();

	if (program)
	{
		// shader attach
		glAttachShader(program, vertexShader);

		glAttachShader(program, fragmentShader);

		// link program handle
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

		if (linkStatus != GL_TRUE) // Error glGetProgramiv
		{
			GLint linkLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &linkLength);

			if (linkLength)
			{
				char *buffer = (char*) malloc(linkLength);
				if (buffer) // Can not link program
				{
					glGetProgramInfoLog(program, linkLength, NULL, buffer);
					free(buffer);
				}
			}

			glDeleteProgram(program);
			program = 0;
		}
	}

	return program;
}


GLuint loadShader(GLuint type, const char* source)
{
	GLuint shader = glCreateShader(type);

	if (shader)
	{
		glShaderSource(shader, 1, &source, NULL);

		glCompileShader(shader);

		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen)
			{
				char *buf = (char*)malloc(infoLen);
				if (buf)
				{
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	}
	return shader;
}
