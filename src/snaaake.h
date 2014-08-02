#ifndef SNAAAKE_H_INCLUDED
#define SNAAAKE_H_INCLUDED

#include "CApp.h"
#include "snaaake_ctrl.h"

#include <deque>
#include <random>

class SnakeApp : public CApp
{
	public:
		typedef CApp Base;

	private:
		int mLoopCount;
		int mDiedOnFrame;

		int mPaused;
		int mPendingGrowth;
		int mSpawnCooldown;
		Point mDir;
		
		std::deque< Point > mPos;
		std::deque< Point > mOther;
		Point mPendingRemove;
		std::mt19937 mRNG;
		int mScore;
		int mHighScore;
    
        SnakeController* mSnakeController;
				
		bool FreeRect(Point p, Point s)const;
		int SpawnDistance(Point r)const;
		Point SpawnPoint();
		void Spawn(int i);
        void Spawn(const Point& p, int i);
		int Consume(Point::BaseType pos);
		void Reset();
		// returns true if the snake lives on, false is death
		bool Occupy( Point pos );
		Point Other( Point pos, Point dir)const;
		void AdvanceTail();
		Point RemoveSpawn(int c, Point near);
		Point Wrap(const Point::BaseType& p)const;
		Point Advance(
			const Point& p,
			const Point::BaseType& d)const;
		
    public:
        SnakeApp();
        inline bool GamePaused() const { return mPaused; }
    
    public:
        virtual bool OnInit();
        virtual void OnEvent(SDL_Event* Event);
        virtual void OnLoop();

};

#endif //SNAAAKE_H_INCLUDED
