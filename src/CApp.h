//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL/SDL_opengl.h>
#include "vector2d.h"

#include <deque>

//==============================================================================
class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

		int mWidth, mHeight;
		
		int mHorizontal, mVertical;
		int* mPixels;
		
		// Geometry::Vector2d< int > mPos;
		Geometry::Vector2d< int > mDir;
		std::deque< Geometry::Vector2d<int> > mEvents;
		std::deque< Geometry::Vector2d<int> > mPos;
		
		GLuint mProgramObject;
		
		int* GetPx( const Geometry::Vector2d< int >& p ) {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		const int * GetPx( const Geometry::Vector2d< int >& p ) const {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		Geometry::Vector2d<int> SpawnPoint(Geometry::Vector2d<int> exclude)const;
		void Reset();
		
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
