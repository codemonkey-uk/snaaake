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
				mDir[0] = -1;
				mDir[1] = 0;
				break;
			case SDLK_d:
    		case SDLK_RIGHT:
				mDir[0] = 1;
				mDir[1] = 0;
				break;
			case SDLK_w:
    		case SDLK_UP:
				mDir[0] = 0;
				mDir[1] = 1;
				break;
			case SDLK_s:
    		case SDLK_DOWN:
				mDir[0] = 0;
				mDir[1] = -1;
				break;
		}
    }
}

//==============================================================================
