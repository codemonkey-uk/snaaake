/*
 *  ring.h
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 07/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#ifndef RING_H_INCLUDED
#define RING_H_INCLUDED

#include "shape.h"

namespace Entropy {

    namespace GFX {

        class Ring : public Shape
        {
            public:
                Ring(GLuint program, int sides, float thickness);
        };
    }
}

#endif