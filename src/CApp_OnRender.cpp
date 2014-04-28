//==============================================================================
#include "CApp.h"

#include "star.h"
#include "ring.h"
#include "quad.h"
#include "geometry_constants.h"

//==============================================================================
void CApp::OnRender() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
	// Set the viewport
	glViewport(0, 0, mWidth, mHeight);
		
	static float r=0;
    r=r+0.1;
    if (r>1) r-=1;
        
    static Entropy::GFX::Shape* g = 
		new Entropy::GFX::Quad(mProgramObject, 0.75f, 0.75f);
	
	int s=84;
	int hs=s/2;
    for (int x=0;x!=s;x++)
    {
	    for (int y=0;y!=48;y++)
    	{
			g->Draw(
				Geometry::Vector2d<float>((x-hs)/float(hs), (18+y-hs)/float(hs)), 
				1.f/s, 
				x+r*Geometry::pi,
				Entropy::GFX::Colour(sin(float(x)/s+r),1,sin(float(y)/s+r)));
		}
	}

	SDL_GL_SwapBuffers();
}

//==============================================================================
