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
				mDx = -1;
				mDy = 0;
				break;
			case SDLK_d:
    		case SDLK_RIGHT:
				mDx = 1;
				mDy = 0;
				break;
			case SDLK_w:
    		case SDLK_UP:
				mDx = 0;
				mDy = 1;
				break;
			case SDLK_s:
    		case SDLK_DOWN:
				mDx = 0;
				mDy = -1;
				break;
		}
    }
}

//==============================================================================
