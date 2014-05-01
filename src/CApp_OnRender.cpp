//==============================================================================
#include "CApp.h"

#include "star.h"
#include "ring.h"
#include "quad.h"
#include "geometry_constants.h"

#include <algorithm>

//==============================================================================
void CApp::OnRender() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
	// Set the viewport
	int s=std::max(mWidth,mHeight);
	glViewport(0, 0, s, s);
		
	static float r=0;
    r=r+0.1;
    if (r>1) r-=1;
        
    static Entropy::GFX::Shape* g = 
		new Entropy::GFX::Quad(mProgramObject, 0.8f, 0.8f);
	
	Entropy::GFX::Colour colours[] = {
		{0.5,0.75,0.5},
		{0,0.25,0},
		{0.75,1,0.75}
	};
	
	int hs=mHorizontal/2;
	float rx=0.6f/hs;
    for (int x=0;x!=mHorizontal;x++)
    {
	    for (int y=0;y!=48;y++)
    	{
    		int i = *(mPixels + x + y*mHorizontal);
			g->Draw(
				Geometry::Vector2d<float>(rx+(x-hs)/float(hs), (18+y-hs)/float(hs)), 
				1.f/mHorizontal, 
				0,
				colours[i]
			);
		}
	}

	SDL_GL_SwapBuffers();
}

//==============================================================================
