/*
 *  ring.cpp
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 07/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#include "ring.h"


#include <math.h>

namespace GFX
{
    Ring::Ring(GLuint program, int sides, float thickness)
        : Shape(program, GL_TRIANGLE_STRIP, sides*2 )
    {
        float outer_r = 1.0f;
        float inner_r = outer_r - thickness;
        float p = (3.14159265f) / (sides-1);

        GLfloat* v = mVertArray;
        for (int i = 0; i!=sides; ++i )
        {
            *v++ = inner_r*sinf( p*i*2 );
            *v++ = inner_r*cosf( p*i*2 );
            *v++ = outer_r*sinf( p*(i*2+1) );
            *v++ = outer_r*cosf( p*(i*2+1) );
        }
    };
}