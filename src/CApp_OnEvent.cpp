//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
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
		}
    }
}

//==============================================================================
