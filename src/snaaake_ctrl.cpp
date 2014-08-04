//
//  snaaake_ctrl.cpp
//  SNAAAKE
//
//  Created by Thaddaeus Frogley on 25/07/2014.
//  Copyright (c) 2014 Thaddaeus Frogley. All rights reserved.
//

#include "snaaake_ctrl.h"
#include "snaaake.h"

#include <algorithm>

// class SnakePlayerController

// for input handling forwarded from the app
// TODO: should be registered with app as input observer
void SnakePlayerController::OnEvent(SDL_Event* Event)
{
    if (Event->type==SDL_KEYDOWN)
    {
    	switch (Event->key.keysym.sym)
    	{
    		case SDLK_a:
    		case SDLK_LEFT:
		    	mEvents.push_back({-1,0});
				break;
			case SDLK_d:
    		case SDLK_RIGHT:
		    	mEvents.push_back({1,0});
				break;
			case SDLK_w:
    		case SDLK_UP:
		    	mEvents.push_back({0,1});
		    	break;
			case SDLK_s:
    		case SDLK_DOWN:
		    	mEvents.push_back({0,-1});
				break;
			default:
				break;
		}
    }
}

void SnakePlayerController::Update(const SnakeApp* pApp)
{
    if (pApp->GamePaused())
    {
        // all game input events are dropped while paused
		if (!mEvents.empty()) mEvents.pop_front();
    }
    
    mInputLatch.Update();
}

CApp::Point SnakePlayerController::GetDirection(CApp::Point dir)
{
    if (!mEvents.empty() && !mInputLatch.IsLocked(mEvents.front()))
    {
        // a change in direction, not reversing direction
        if (mEvents.front()!=-dir && mEvents.front()!=dir)
        {
            mInputLatch.Lock(2, -dir);
            dir = mEvents.front();
        }
        mEvents.pop_front();
    }
    
    return dir;
}

void SnakePlayerController::Reset()
{
    mEvents.clear();
}

// ---

// class SnakePlayerController

void SnakeAIController::OnEvent(SDL_Event* Event)
{
    // Nothing to do:
    // App will end AI game when player interacts
}

const CApp::Point directions[] = { {1,0},{-1,0},{0,1},{0,-1} };

int SnakeAIController::Score(CApp::Point p, int d, const SnakeApp* pApp)const
{
    int score = 1;
    int collides = 0;
    
    CApp::Point o(Geometry::uninitialised);
    do {
        p = pApp->Advance(p, directions[d]);
        o = pApp->Other(p, directions[d]);
        score++;
        
        collides = *pApp->GetPx(p);
        collides = std::max(collides, *pApp->GetPx(o));

    }while (collides==0);
    
    if (collides==2)
    {
        score = INT16_MAX-score;
    }
    
    return score;
}

void SnakeAIController::Update(const SnakeApp* pApp)
{
    static int mCD = 2;
    if (pApp->Alive())
    {
        int score[] = {0,0,0,0};
        
        CApp::Point start = pApp->GetHead();
        const CApp::Point cDir = pApp->GetDir();
        for (int d=0;d!=4;++d)
        {
            CApp::Point p = start;

            // turning logic:
            if (directions[d]!=cDir)
            {
                if (directions[d][1]==1 || directions[d][0]==1)
                    p = pApp->Advance(p, directions[d]);
                if (cDir[1]==1 || cDir[0]==1)
					p = pApp->Advance( p, -cDir );
            }
            
            score[d] = Score(p, d, pApp);
        }
        
        int b=0;
        for (int d=1;d!=4;++d)
            if (score[d]>score[b]) b=d;
        
        if (mDir!=b && score[mDir] < score[b]-score[mDir] )
        {
            if ((mRNG()%mCD)==0)
            {
                mDir = b;
                if (mCD<4) mCD += 2;
                else mCD += 12;
            }
        }
    }
    
    if (mCD>2) mCD--;
}

CApp::Point SnakeAIController::GetDirection(CApp::Point dir)
{
    return directions[mDir];
}

void SnakeAIController::Reset()
{
    // Nothing to do
}

