#ifndef TRIANGLE_BATCHER_H_INCLUDED
#define TRIANGLE_BATCHER_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "matrixn.h"
#include "colour.h"

class TriangleBatcher
{
	public:
		TriangleBatcher(GLuint program, int traingleCapacity);
        
        ~TriangleBatcher();
        
        void AddTriangles(const GLfloat* verts, int tc);
        
        void Flush(const GFX::Colour& col);
		void Flush(
			const Geometry::MatrixN<float,4>& matrix, 
			const GFX::Colour& col);
		
	private:
		static const GLenum mMode = GL_TRIANGLES;
		const GLint mMaxVert;
		GLfloat * const mVertArray;
		
		GLint mVertCount;

		GLint mProgram;
		int mTransformUniform;
		int mColourUniform;
};

#endif//TRIANGLE_BATCHER_H_INCLUDED