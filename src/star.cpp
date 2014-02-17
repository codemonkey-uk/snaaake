/*
 *  star.cpp
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 08/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#include "star.h"

#include <math.h>

namespace Entropy {

    namespace GFX {

        Star::Star(GLuint program, int points, float thickness)
            : Shape(program, GL_TRIANGLES, points*3)
        {
            float outer_r = 1.0f;
            float inner_r = outer_r - thickness;
            float p = (3.14159265f * 2) / (points*2);

            GLfloat* v = mVertArray;
            for (int i = 0; i!=points; ++i )
            {
                *v++ = inner_r*sinf( p*i*2 );
                *v++ = inner_r*cosf( p*i*2 );
                *v++ = outer_r*sinf( p*(i*2+1) );
                *v++ = outer_r*cosf( p*(i*2+1) );
                *v++ = inner_r*sinf( p*(i*2+2) );
                *v++ = inner_r*cosf( p*(i*2+2) );
            }
        };
    }
}