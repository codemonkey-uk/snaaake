//==============================================================================
#include "CApp.h"

#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <emscripten/emscripten.h>

#include "SDL/SDL_opengl.h"

//
// Create a shader object, load the shader source, and compile the shader.
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
	const char* vShaderStr =
		"attribute vec4 vPosition;\n"
		"uniform mat4 transform;\n"
		"uniform mediump vec4 colour;\n"
		"varying mediump vec4 colourOut;\n"
		"void main()\n"
		"{\n"
		"  colourOut = colour;\n"
		"  gl_Position = transform*vPosition;\n"
		"}\n";

	const char* fShaderStr =
		"precision mediump float;\n"
		"varying mediump vec4 colourOut;\n"
		"void main()"
		"{"
		" gl_FragColor = colourOut; " 
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

   return programObject;
}

//==============================================================================
bool CApp::OnInit() 
{	
	mHorizontal=84;
	mVertical=48;

	mWidth=6*mHorizontal;
	mHeight=6*mVertical;

	mPixels=new int[mHorizontal*mVertical];

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

	const int hs=mHorizontal/2;
	const float rx=0.75f/hs;
	mQuads = (Entropy::GFX::Quad*)malloc( sizeof(Entropy::GFX::Quad)*mHorizontal*mVertical );
	for (int x=0;x!=mHorizontal;x++)
    {
	    for (int y=0;y!=mVertical;y++)
    	{
			Entropy::GFX::Quad* pQ = GetQx( {x,y} );
			new(pQ) Entropy::GFX::Quad(mProgramObject, 0.8f, 0.8f);
			pQ->Pretransform( 
				Geometry::Vector2d<float>(rx+(x-hs)/float(hs), rx+(y-hs)/float(hs)), 
				1.f/mHorizontal, 
				0 );
    	}
	}
	
    return true;
}

//==============================================================================
