/*
 *  shape.cpp
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 12/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#include "shape.h"

#include <stdlib.h>
#include <stdio.h>
 
#include "matrixnm.h"
#include "matrixn.h"
 
namespace Entropy {

    namespace GFX {
    
        Shape::Shape(GLuint program, GLenum mode, int verts)
            : mProgram(program)
            , mMode(mode)
            , mVertCount( verts )
            , mVertArray( new GLfloat[ verts*2 ] )
        {
			mTransformUniform = glGetUniformLocation(mProgram, "transform");
			if (mTransformUniform==-1) printf("Transform Uniform not found.\n");
			mColourUniform = glGetUniformLocation(mProgram, "colour");
			if (mColourUniform==-1) printf("Colour Uniform not found.\n");
        }
        
        Shape::~Shape()
        {
            delete[] mVertArray;
        }
        
        void Shape::Draw(
            const Geometry::VectorN<float, 2>& p, 
            float size, 
            float spin,
            const Colour& col) const
        {
        	// Use the program object 
			glUseProgram(mProgram);
			
			Geometry::MatrixN<float,4> scale(Geometry::uninitialised);
			scale.Scale(size);
			
			Geometry::MatrixN<float,4> translate({
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				p.Get(0), p.Get(1), 0, 1
			});
			
			Geometry::MatrixN<float,4> matrix = scale * translate;
			
			glUniformMatrix4fv( mTransformUniform, 1, GL_FALSE, matrix[0] );			
			glUniform4f(mColourUniform, col.mR, col.mG, col.mB, 1.0f);
			
            // glRotatef( spin, 0,0,1);
            
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, mVertArray); 
			glEnableVertexAttribArray(0);
	     
            // glVertexPointer(2, GL_FLOAT, 0, mVertArray);
            // glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(mMode, 0, mVertCount);
            
            // glPopMatrix();
        }
        
    }
}