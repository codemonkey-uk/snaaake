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

    private:
        bool            Running;

		// rendering / pixel access
		
        SDL_Surface*    Surf_Display;
		GLuint mProgramObject;
		
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
		Point mDir;
		std::deque< Point > mEvents;

		std::deque< Point > mPos;
		std::deque< Point > mOther;
		Point mPendingRemove;
		std::mt19937 mRNG;
		int mScore;
		int mHighScore;
				
		bool FreeRect(Point p, Point s);
		Point SpawnPoint(Point exclude);
		void Spawn(Point e, int i);
		int Consume( Point::BaseType pos );
		void Reset();
		// returns true if the snake lives on, false is death
		bool Occupy( Point pos );
		Point Other( Point pos, Point dir);
		void AdvanceTail();
		Point RemoveSpawn(int c, Point near);
		Point Wrap(const Point::BaseType& p)const;
		Point Advance(
			const Point& p,
			const Point::BaseType& d);
			
	public:
        void OnRender();
        void OnCleanup();

    public:
        CApp();
        int OnExecute(int fps);

    public:
        virtual bool OnInit();
        virtual void OnEvent(SDL_Event* Event);
        virtual void OnLoop();

};

//==============================================================================

#endif
