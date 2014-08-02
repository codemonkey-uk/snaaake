//
//  snaaake_ctrl.cpp
//  SNAAAKE
//
//  Created by Thaddaeus Frogley on 25/07/2014.
//  Copyright (c) 2014 Thaddaeus Frogley. All rights reserved.
//

#include "snaaake_ctrl.h"
#include "snaaake.h"

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

// for input handling forwarded from the app
// TODO: should be registered with app as input observer
void SnakeAIController::OnEvent(SDL_Event* Event)
{
    // TODO: End AI game when players interact
}

void SnakeAIController::Update(const SnakeApp* pApp)
{
    static int mCD = 0;
    if (pApp->Alive() && mCD-- <= 0)
    {
        const CApp::Point directions[] = { {1,0},{-1,0},{0,1},{0,-1} };
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
            
            CApp::Point o(Geometry::uninitialised);
            do {
                p = pApp->Advance(p, directions[d]);
                o = pApp->Other(p, directions[d]);
                score[d]++;
            }while (*pApp->GetPx(p)==0 && *pApp->GetPx(o)==0);

            if (*pApp->GetPx(p)==2 || *pApp->GetPx(o)==2)
                score[d] = INT32_MAX-score[d];
        }
        int b=0;
        for (int d=1;d!=4;++d)
            if (score[d]-2>score[b]) b=d;
        
        if (mDir!=directions[b])
        {
            mDir = directions[b];
            mCD = 2;
        }
    }
}

CApp::Point SnakeAIController::GetDirection(CApp::Point dir)
{
    return mDir;
}

void SnakeAIController::Reset()
{
    // Nothing to do
}

