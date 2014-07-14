//==============================================================================
#include "CApp.h"

#include "shape.h"
#include "geometry_constants.h"
#include "font.h"

#include <algorithm>
#include <stdio.h>

class TriangleBatcher
{
	public:
		TriangleBatcher(GLuint program, int traingleCapacity)
            : mProgram(program)
            , mMaxVert(traingleCapacity*3)
            , mVertArray( new GLfloat[mMaxVert*2] )
			, mVertCount(0)
        {
			mTransformUniform = glGetUniformLocation(mProgram, "transform");
			if (mTransformUniform==-1) printf("Transform Uniform not found.\n");
			mColourUniform = glGetUniformLocation(mProgram, "colour");
			if (mColourUniform==-1) printf("Colour Uniform not found.\n");
        }
        
        ~TriangleBatcher()
        {
        	delete [] mVertArray;
        }
        
        void AddTriangles(const GLfloat* verts, int tc)
        {
			int vc = tc*3;
        	if (mVertCount + vc < mMaxVert)
        	{
	        	memcpy(mVertArray+mVertCount*2, verts, vc*2*sizeof(GLfloat));
    	    	mVertCount += vc;
    	    }
        }
        
        void Flush(const Entropy::GFX::Colour& col) 
		{
			Geometry::MatrixN<float,4> identity;
			Flush( identity, col );
		}
		
		void Flush(
			const Geometry::MatrixN<float,4>& matrix, 
			const Entropy::GFX::Colour& col) 
		{
			if (mVertCount>0)
			{			
				// Use the program object 
				glUseProgram(mProgram);
			
				glUniformMatrix4fv( mTransformUniform, 1, GL_FALSE, matrix[0] );			
				glUniform4f(mColourUniform, col.mR, col.mG, col.mB, 1.0f);
			
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, mVertArray); 
				glEnableVertexAttribArray(0);
		 
				glDrawArrays(mMode, 0, mVertCount);	
			
				mVertCount = 0;	
			}
		}
		
	private:
		// all set up in the initialiser list of the Shape constructor
		static const GLenum mMode = GL_TRIANGLES;
		const GLint mMaxVert;
		GLfloat * const mVertArray;
		
		GLint mVertCount;

		GLint mProgram;
		int mTransformUniform;
		int mColourUniform;
};

void CApp::PrintString( const char* buffer, int h, int v, HAlign align)	
{
	using namespace Font;
	
	int l=static_cast<int>(strlen(buffer));
	int x = h;
	if (align==Right) x = h - l*4;
	else if (align==Center) x = h - (l*4)/2;
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(GetGlyph(buffer[i]), x, v, mPixels, mHorizontal, mVertical);
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
	
	static const Entropy::GFX::Colour colours[] = {
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
