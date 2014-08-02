//
//  snaaake_ctrl.cpp
//  SNAAAKE
//
//  Created by Thaddaeus Frogley on 25/07/2014.
//  Copyright (c) 2014 Thaddaeus Frogley. All rights reserved.
//

#include "snaaake_ctrl.h"
#include "snaaake.h"

// class SnakeController

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
