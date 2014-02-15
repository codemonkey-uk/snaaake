//==============================================================================
#include "CApp.h"

#include <stdlib.h>
#include <stdio.h>

// #include <GL/glfw.h>
#include <emscripten/emscripten.h>

#include "SDL/SDL_opengl.h"


///
// Create a shader object, load the shader source, and // compile the shader.
//
GLuint LoadShader(const char *shaderSrc, GLenum type) 
{
	GLuint shader; 
	GLint compiled;

	// Create the shader object 
	shader = glCreateShader(type);
	if(shader == 0)
		return 0;
		
	// Load the shader source 
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// Compile the shader 
	glCompileShader(shader);
	
	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled) 
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 1)
      	{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog); 
			printf("Error compiling shader:\n%s\n%s\n", infoLog, shaderSrc); 
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0; 
	}
	return shader; 
}

int Init()
{
	// !!! UserData *userData = esContext->userData; 
	
	const char* vShaderStr =
		"attribute vec4 vPosition;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vPosition;\n"
		"}\n";

	const char* fShaderStr =
		"precision mediump float;\n"
		"void main()"
		"{"
		" gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); " 
		"}";
		
	GLuint vertexShader; 
	GLuint fragmentShader; 
	GLuint programObject; 
	GLint linked;
	
	vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER); 
	fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);
	
	// Create the program object 
	programObject = glCreateProgram();
	if(programObject == 0) return 0;
	
	glAttachShader(programObject, vertexShader); 
	glAttachShader(programObject, fragmentShader);
	
	// Bind vPosition to attribute 0 
	glBindAttribLocation(programObject, 0, "vPosition");
	// Link the program 
	glLinkProgram(programObject);
	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if(!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
      	if(infoLen > 1)
      	{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog); 
			printf("Error linking program:\n%s\n", infoLog);
			free(infoLog); 
		}
		glDeleteProgram(programObject);
      	return 0;
   }

	// Store the program object 
	// userData->programObject = programObject;
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   return programObject;
}

//==============================================================================
bool CApp::OnInit() {

	mWidth=640;
	mHeight=480;
	/*
    if (glfwInit() != GL_TRUE) {
        printf("glfwInit() failed\n");
        return GL_FALSE;
    }
 
    if (glfwOpenWindow(mWidth, mHeight, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE) {
        printf("glfwOpenWindow() failed\n");
        return GL_FALSE;
    }*/
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;    
    }
    
    //Create Window
    if( SDL_SetVideoMode( mWidth, mHeight, 24, SDL_OPENGL ) == NULL )
    {
        return false;
    }

	mProgramObject = Init();
	
    return true;
}

//==============================================================================
