//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL/SDL_opengl.h>
#include "vector2d.h"

#include <deque>
#include <random>

//==============================================================================
class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;

		int mWidth, mHeight;
		int mHorizontal, mVertical;
		
		int* mPixels;
		int mLoopCount;
		
		int mPendingGrowth;
		Geometry::Vector2d< int > mDir;
		std::deque< Geometry::Vector2d<int> > mEvents;

		std::deque< Geometry::Vector2d<int> > mPos;
		std::deque< Geometry::Vector2d<int> > mOther;
		
		std::mt19937 mRNG;
		
		GLuint mProgramObject;
		
		int* GetPx( const Geometry::Vector2d< int >::BaseType& p ) {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		const int * GetPx( const Geometry::Vector2d< int >::BaseType& p ) const {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		void PrintNumber( int num, int h, int v, bool ralign);
		
		Geometry::Vector2d<int> SpawnPoint(Geometry::Vector2d<int> exclude);
		void Reset();
		// returns true if the snake lives on, false is death
		bool Occupy( Geometry::Vector2d<int> pos );
		
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
