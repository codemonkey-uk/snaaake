//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL/SDL_opengl.h>

//==============================================================================
class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

		int mWidth, mHeight;
		
		int mHorizontal, mVertical;
		int* mPixels;
		
		int mX,mY;
		int mDx,mDy;
		
		GLuint mProgramObject;
		
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
