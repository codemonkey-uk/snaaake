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
			
			/*
			Geometry::MatrixNM<float,4,4> matrix(Geometry::uninitialised);
			matrix[0][0]=size;
			matrix[0][1]=0;
			matrix[0][2]=0;
			matrix[0][3]=0;
			matrix[1][0]=0;
			matrix[1][1]=size;
			matrix[1][2]=0;
			matrix[1][3]=0;
			matrix[2][0]=0;
			matrix[2][1]=0;
			matrix[2][2]=size;
			matrix[2][3]=0;
			matrix[3][0]=p.Get(0);
			matrix[3][1]=p.Get(1);
			matrix[3][2]=0;
			matrix[3][3]=1;
			*/
			float data[4*4] = {
				size, 0, 0, 0,
				0, size, 0, 0,
				0, 0, size, 0,
				p.Get(0), p.Get(1), 0, 1
			};
			Geometry::MatrixNM<float,4,4> matrix(data);
			
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