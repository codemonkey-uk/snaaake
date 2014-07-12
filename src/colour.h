/*
 *  colour.h
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 08/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */

#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

// #include <OpenGLES/ES1/gl.h>

#ifdef EMSCRIPTEN
#include <GL/glfw.h>
#else
#include <OpenGL/gl.h>
#endif

namespace Entropy 
{
    namespace GFX
    {
        class Colour
        {
            public:
                Colour( GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.0f )
                    : mR(r)
                    , mG(g)
                    , mB(b)
                    , mA(a)
                {}
                    
                void Draw()const
                {
                    glColor4f( mR, mG, mB, mA );
                }
                
                void ApplyAlpha()
                {
                    mR = mR*mA;
                    mG = mG*mA;
                    mB = mB*mA;
                }
                
            //private:
                GLfloat mR, mG, mB, mA;
                
        };
        
        extern Colour colours[];
    }
}

#endif