/*
 *  star.cpp
 *
 *  Created by Thaddaeus Frogley on 2014.
 *  Copyright 2014 Thaddaeus Frogley. All rights reserved.
 *
 */

#include "quad.h"

#include <math.h>

namespace Entropy {

    namespace GFX {

        Quad::Quad(GLuint program, float w, float h)
            : Shape(program, GL_TRIANGLES, 6)
        {
            GLfloat* v = mVertArray; // v for verts
            const GLfloat x =  -w/2;
            const GLfloat y =  -h/2;
            
            // 1st Tri of Quad: 0,1,2
            
            // 0 (top left)
            *v++ = x - w;
            *v++ = y + h;
            
            // 1 (top right)
            *v++ = x + w;
            *v++ = y + h;

            // 2 (bottom left)
            *v++ = x - w;
            *v++ = y - h;
            
            // 2nd Tri of Quad 132
            
            // 1 (top right)
            *v++ = x + w;
            *v++ = y + h;

            // 3 (bottom right)
            *v++ = x + w;
            *v++ = y - h;
            
            // 2 (bottom left)
            *v++ = x - w;
            *v++ = y - h;
        };
    }
}