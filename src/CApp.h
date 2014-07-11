//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL/SDL_opengl.h>

#include "vector2d.h"
#include "quad.h"
#include "InputLatch.h"

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
		Entropy::GFX::Quad* mQuads;
		
		// gameplay
		int mLoopCount;
		int mDiedOnFrame;

		InputLatch mInputLatch;
		
		int mPaused;
		int mPendingGrowth;
		int mSpawnCooldown;
		Geometry::Vector2d< int > mDir;
		std::deque< Geometry::Vector2d<int> > mEvents;

		std::deque< Geometry::Vector2d<int> > mPos;
		std::deque< Geometry::Vector2d<int> > mOther;
		Geometry::Vector2d<int> mPendingRemove;
		std::mt19937 mRNG;
		int mScore;
		int mHighScore;
		
		GLuint mProgramObject;
		
		int* GetPx( const Geometry::Vector2d< int >::BaseType& p ) {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		const int * GetPx( const Geometry::Vector2d< int >::BaseType& p ) const {
			return (mPixels + p[0] + p[1]*mHorizontal);
		}
		Entropy::GFX::Quad* GetQx( const Geometry::Vector2d< int >::BaseType& p ) {
			return (mQuads + p[0] + p[1]*mHorizontal);
		}
		
		enum HAlign { Left, Center, Right };
		void PrintString( const char* buffer, int h, int v, HAlign align);
		void PrintNumber( int num, int h, int v, HAlign align);
		
		bool FreeRect(Geometry::Vector2d<int> p, Geometry::Vector2d<int> s);
		Geometry::Vector2d<int> SpawnPoint(Geometry::Vector2d<int> exclude);
		void Spawn(Geometry::Vector2d<int> e, int i);
		int Consume( Geometry::Vector2d<int>::BaseType pos );
		void Reset();
		// returns true if the snake lives on, false is death
		bool Occupy( Geometry::Vector2d<int> pos );
		Geometry::Vector2d<int> Other(
			Geometry::Vector2d<int> pos, 
			Geometry::Vector2d<int> dir);
		void AdvanceTail();
		Geometry::Vector2d<int> RemoveSpawn(int c, Geometry::Vector2d<int> near);
		Geometry::Vector2d<int> Wrap(const Geometry::Vector2d<int>::BaseType& p)const;
		Geometry::Vector2d<int> Advance(
			const Geometry::Vector2d<int>& p,
			const Geometry::Vector2d<int>::BaseType& d);
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
