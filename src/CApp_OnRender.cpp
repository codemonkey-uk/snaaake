//==============================================================================
#include "CApp.h"
#include <GL/glfw.h>

#include "star.h"
#include "geometry_constants.h"
//==============================================================================
void CApp::OnRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	/*
    glLoadIdentity();
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
    glEnd();
	*/
	/*
	GLfloat vertices[] = {1,0,0, 0,1,0, -1,0,0};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	
	// This application only creates a single default framebuffer which is already bound at this point.
	// This call is redundant, but needed if dealing with multiple framebuffers.
    /*
    glViewport(0, 0, mWidth, mHeight);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glScalef( 1.0f, (float)mWidth / (float)mHeight, 1.0f );
	*/
	static float r=0;
    r=r+0.01;
    if (r>1) r-=1;
        
    glClearColor(r, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    static Entropy::GFX::Shape* g = new Entropy::GFX::Star(6, 0.25f);
    g->Draw(Geometry::Vector2d<float>(0.0f,0.0f), 
                    1, 
                    r*360,
                    Entropy::GFX::Colour(1,1,1));
    
    // hack background  
    /*
            const float h = (480.f / 320.f);
            static GLfloat verts[] = {
                -1,-h,
                -1, h,
                 1, h,
                 1,-h
            };
            
            glPushMatrix();
            // col.Draw();
                    
            // glEnable(GL_TEXTURE_2D);
            glDisable(GL_BLEND);
            // mTexture.Bind();

            glVertexPointer(2, GL_FLOAT, 0, verts);
            //glTexCoordPointer(2, GL_FLOAT, 0, mUVs );
            glEnableClientState(GL_VERTEX_ARRAY);
            //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            
            glPopMatrix();
      */      
    glfwSwapBuffers();
}

//==============================================================================
