/*
 *  star.h
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 08/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

#include "shape.h"

namespace Entropy {

    namespace GFX {

        class Star : public Shape
        {
            public:
                Star(GLuint program, int points, float thickness);                
        };
    }
}

#endif