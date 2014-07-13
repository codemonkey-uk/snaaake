//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef CAPP_H_INCLUDED
#define CAPP_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "vector2d.h"
#include "quad.h"
		
//==============================================================================
class CApp {
	public:
		typedef Geometry::Vector2d< int > Point;
		
		inline int* GetPx( const Point::BaseType& p ) {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		inline const int * GetPx( const Point::BaseType& p ) const {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		inline Entropy::GFX::Quad* GetQx( const Point::BaseType& p ) {
			return (mQuads + p[0] + p[1]*mHorizontal);
		}

		enum HAlign { Left, Center, Right };
		void PrintString( const char* buffer, int h, int v, HAlign align);
		void PrintNumber( int num, int h, int v, HAlign align);

		void Clear(int c) {
			std::fill(mPixels, mPixels+(mHorizontal*mVertical), c);
		}
		void ClearRows(int first, int last, int c) {
			std::fill(mPixels+(mHorizontal*first), mPixels+(mHorizontal*last), c);
		}
    private:
        bool            Running;

		// rendering / pixel access
		
        SDL_Surface*    Surf_Display;
		GLuint mProgramObject;
		
		int mWidth, mHeight;
		
		int* mPixels;
		Entropy::GFX::Quad* mQuads;

	protected:
		int mHorizontal, mVertical;
	
	public:
        void OnRender();
        void OnCleanup();

    public:
        CApp();
        int OnExecute(int fps);

    public:
        virtual bool OnInit();
        virtual void OnEvent(SDL_Event* Event);
        virtual void OnLoop()=0;

};

//==============================================================================

#endif //CAPP_H_INCLUDED
