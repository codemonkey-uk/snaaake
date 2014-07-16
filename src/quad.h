/*
 *  quad.h
 *  Created by Thaddaeus Frogley 2014.
 *  Copyright 2014 Thaddaeus Frogley. All rights reserved.
 *
 */

#ifndef QUAD_H_INCLUDED
#define QUAD_H_INCLUDED

#include "shape.h"

namespace GFX
{
    class Quad : public Shape
    {
        public:
            Quad(GLuint program, float w, float h); 
            const GLfloat* GetVerts() const {
                return mVertArray;
            }
    };
}

#endif