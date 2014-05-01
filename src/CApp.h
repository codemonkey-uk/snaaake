//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL/SDL_opengl.h>
#include "vector2d.h"

//==============================================================================
class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

		int mWidth, mHeight;
		
		int mHorizontal, mVertical;
		int* mPixels;
		
		Geometry::Vector2d< int > mPos;
		Geometry::Vector2d< int > mDir;
		
		GLuint mProgramObject;
		
		int* GetPx( const Geometry::Vector2d< int >& p ) {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		
    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

//==============================================================================

#endif
