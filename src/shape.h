/*
 *  shape.h
 *  iEntropy
 *
 *  Created by Thaddaeus Frogley on 12/02/2010.
 *  Copyright 2010 Thaddaeus Frogley. All rights reserved.
 *
 */


#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

// #include <OpenGLES/ES1/gl.h>
// #include <GL/glfw.h>
#include "SDL/SDL_opengl.h"


#include "vectorn.h"
#include "colour.h"
#include "aabb2d.h"

namespace Entropy {

    namespace GFX {
    
        typedef Geometry::AxisAlignedBoundingBox2d< GLfloat > AABB;

        class Shape
        {
            public:
                virtual void Draw(
                    const Geometry::VectorN<float, 2>& p, 
                    float size, 
                    float rotation,
                    const Colour& col) const;
                virtual ~Shape();
                
            protected:
                // shape is a base class for drawing procedural geometry,
                // which is created in the constructor of derived classes
                Shape(GLuint program, GLenum mode, int verts); 

                // all set up in the initialiser list of the Shape constructor
                const GLenum mMode;
                const GLint mVertCount;
                GLfloat * const mVertArray;
                
                GLint mProgram;
                int mScaleUniform;
                int mTranslateUniform;
                int mColourUniform;
                
        };
    }
}

#endif