#ifndef SNAAAKE_H_INCLUDED
#define SNAAAKE_H_INCLUDED

#include "CApp.h"
#include "InputLatch.h"

#include <deque>
#include <random>

class SnakeApp : public CApp
{
	public:
		typedef CApp Base;
		// gameplay
	private:

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
        SnakeApp();

    public:
        virtual bool OnInit();
        virtual void OnEvent(SDL_Event* Event);
        virtual void OnLoop();

};

#endif //SNAAAKE_H_INCLUDED
