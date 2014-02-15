//==============================================================================
#include "CApp.h"
// #include <GL/glfw.h>

#include "star.h"
#include "geometry_constants.h"

//==============================================================================
void CApp::OnRender() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*
	static float r=0;
    r=r+0.01;
    if (r>1) r-=1;
        
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    static Entropy::GFX::Shape* g = new Entropy::GFX::Star(8, 0.6f);
    for (int i=0;i!=16;++i)
    {
    	float t = r*Geometry::pi*2 + i/Geometry::pi*6;
		g->Draw(Geometry::Vector2d<float>(i/8.0 * sinf(t)/2, i/8.0 * cosf(t)/2), 
						0.15, 
						r*360,
						Entropy::GFX::Colour(sin(t),cos(t*4),sin(t*2)));
	}
	*/
      
	GLfloat vVertices[] = {
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f };
		 
	// Set the viewport
	glViewport(0, 0, mWidth, mHeight);
	
	// Clear the color buffer 
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Use the program object 
	glUseProgram(mProgramObject);
	
	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices); 
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapBuffers();
}

//==============================================================================
