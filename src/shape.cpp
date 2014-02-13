/*
 *  shape.cpp
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 12/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#include "shape.h"


namespace Entropy {

    namespace GFX {
    
        Shape::Shape(GLenum mode, int verts)
            : mMode(mode)
            , mVertCount( verts )
            , mVertArray( new GLfloat[ verts*2 ] )
        {
        
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
            glPushMatrix();
            
            glTranslatef( p.Get(0), p.Get(1), 0 );    
            glScalef( size, size, 1.0f );
            glRotatef( spin, 0,0,1);
            col.Draw();
                    
            glVertexPointer(2, GL_FLOAT, 0, mVertArray);
            glEnableClientState(GL_VERTEX_ARRAY);
            glDrawArrays(mMode, 0, mVertCount);
            
            glPopMatrix();
        }
        
    }
}