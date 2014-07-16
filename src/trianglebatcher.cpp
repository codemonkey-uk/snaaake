
#include "trianglebatcher.h"
#include "matrixn.h"

#include <stdio.h>

TriangleBatcher::TriangleBatcher(GLuint program, int traingleCapacity)
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
        
TriangleBatcher::~TriangleBatcher()
{
	delete [] mVertArray;
}

void TriangleBatcher::AddTriangles(const GLfloat* verts, int tc)
{
	int vc = tc*3;
	if (mVertCount + vc < mMaxVert)
	{
		memcpy(mVertArray+mVertCount*2, verts, vc*2*sizeof(GLfloat));
		mVertCount += vc;
	}
}
        
void TriangleBatcher::Flush(const GFX::Colour& col) 
{
	Geometry::MatrixN<float,4> identity;
	Flush( identity, col );
}
		
void TriangleBatcher::Flush(
	const Geometry::MatrixN<float,4>& matrix, 
	const GFX::Colour& col) 
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
