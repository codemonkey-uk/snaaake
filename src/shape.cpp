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

namespace Entropy {

    namespace GFX {
    
        Shape::Shape(GLuint program, GLenum mode, int verts)
            : mProgram(program)
            , mMode(mode)
            , mVertCount( verts )
            , mVertArray( new GLfloat[ verts*2 ] )
        {
        	mScaleUniform = glGetUniformLocation(mProgram, "scale");
			if (mScaleUniform==-1) printf("Scale Uniform not found.\n");
			mTranslateUniform = glGetUniformLocation(mProgram, "translation");
			if (mTranslateUniform==-1) printf("Translate Uniform not found.\n");
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
			glUniform1f(mScaleUniform, size);
			glUniform3f(mTranslateUniform, p.Get(1), p.Get(0), 0);
			
            // glRotatef( spin, 0,0,1);
            // col.Draw();
            
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, mVertArray); 
			glEnableVertexAttribArray(0);
	     
            // glVertexPointer(2, GL_FLOAT, 0, mVertArray);
            // glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(mMode, 0, mVertCount);
            
            // glPopMatrix();
        }
        
    }
}