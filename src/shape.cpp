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
#include "matrix4.h"
 
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
			scale.BecomeScale(size);
			
			Geometry::MatrixN<float,4> translate;
			translate.BecomeTranslation( Geometry::VectorN<float, 3>(p,0) );

			//Geometry::Matrix4<float> rotate = 
			//	Geometry::Matrix4<float>::RotationAroundY(spin)
			//	* Geometry::Matrix4<float>::RotationAroundZ(spin*0.5f)
			//	* Geometry::Matrix4<float>::RotationAroundX(spin*0.25f);
			Geometry::Matrix4<float> rotate(Geometry::uninitialised);
			
			//rotate.BecomeRotationFromEuler( Geometry::VectorN<float, 3>( { spin, 0, 0 } ) );
			//rotate.BecomeRotationAround( Geometry::VectorN<float, 3>( { 0, 0, 1 } ), spin );
			 Geometry::VectorN<float, 3> axis { 1, 1, 0 };
			 axis.Normalise();
			 rotate.BecomeRotationAround(axis, spin );
			
			Geometry::MatrixN<float,4> matrix = scale * rotate * translate;
			
			glUniformMatrix4fv( mTransformUniform, 1, GL_FALSE, matrix[0] );			
			glUniform4f(mColourUniform, col.mR, col.mG, col.mB, 1.0f);
			
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, mVertArray); 
			glEnableVertexAttribArray(0);
	     
            glDrawArrays(mMode, 0, mVertCount);
        }
        
    }
}