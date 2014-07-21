//==============================================================================
#include "CApp.h"

#include "shape.h"
#include "geometry_constants.h"
#include "font.h"
#include "trianglebatcher.h"

#include <algorithm>
#include <stdio.h>

// lineWidth
// == true - return the width of the first line
// == false - return the width of the widest line
int StringWidth( const char* s, bool lineWidth=false )
{
	using namespace Font;
	
	int w=0, lw=0;
	while(*s)
	{
		if (*s=='\n')
		{
			if (lineWidth) return lw;
			lw = 0;
		}
		else 
		{
			lw += Width( GetGlyph(*s) );
		}
		if (lw>w) w = lw;
		++s;
	}
	return w;
}

int LineStart( const char* buffer, int h, CApp::HAlign align)	
{
	int w = StringWidth(buffer, true);
	if (align==CApp::Right) 
		return h - w;
	else if (align==CApp::Center) 
		return h - w/2;
	else return h;
}

void CApp::PrintString( const char* buffer, int h, int v, HAlign align)	
{
	using namespace Font;
	
	int l=static_cast<int>(strlen(buffer));
	int x = LineStart(buffer, h, align);
	for (int i = 0 ; i!=l; ++i)
	{
		if (buffer[i]=='\n')
		{
			v -= 7;
			x = LineStart(buffer+i+1, h, align);
		}
		else
		{
			x+=Blit(GetGlyph(buffer[i]), x, v, mPixels, mHorizontal, mVertical);
		}
	}
}

void CApp::PrintNumber( int num, int h, int v, HAlign align)	
{
	char buffer[8];
	sprintf(buffer,"%i", num);
	PrintString(buffer, h, v, align);
}

//==============================================================================
void CApp::OnRender() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
	// Set the viewport
	int s=std::max(mWidth,mHeight);
	glViewport(0, 0, s, s);
	
	static const GFX::Colour colours[] = {
		{0.5,0.75,0.5},
		{0,0.25,0},
		{0.75,1,0.75}
	};
	
	TriangleBatcher* batches[] = {
		new TriangleBatcher(mProgramObject, mHorizontal*mVertical*2),
		new TriangleBatcher(mProgramObject, mHorizontal*mVertical*2),
		new TriangleBatcher(mProgramObject, mHorizontal*mVertical*2)		
	};
	
    for (int x=0;x!=mHorizontal;x++)
    {
	    for (int y=0;y!=mVertical;y++)
    	{
    		int i = *GetPx( {x,y} );
			batches[i]->AddTriangles(GetQx( {x,y} )->GetVerts(), 2 );
		}
	}

	batches[0]->Flush(colours[0]);
	batches[1]->Flush(colours[1]);
	batches[2]->Flush(colours[2]);
		
	delete batches[0];
	delete batches[1];
	delete batches[2];
	
	SDL_GL_SwapBuffers();
}

//==============================================================================
