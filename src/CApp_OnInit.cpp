//==============================================================================
#include "CApp.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glfw.h>
#include <emscripten/emscripten.h>

//==============================================================================
bool CApp::OnInit() {

	mWidth=640;
	mHeight=480;
	
    if (glfwInit() != GL_TRUE) {
        printf("glfwInit() failed\n");
        return GL_FALSE;
    }
 
    if (glfwOpenWindow(mWidth, mHeight, 8, 8, 8, 8, 16, 0, GLFW_WINDOW) != GL_TRUE) {
        printf("glfwOpenWindow() failed\n");
        return GL_FALSE;
    }

    return true;
}

//==============================================================================
