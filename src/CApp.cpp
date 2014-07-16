//==============================================================================
#include "CApp.h"
#include <stdio.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#else
#include <unistd.h>
#endif

//==============================================================================
CApp::CApp()
{
    Surf_Display = NULL;
    Running = true;
}

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) 
{
    if(Event->type == SDL_QUIT) 
    {
        Running = false;
    }
}

//==============================================================================
void CApp::OnCleanup() 
{
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

//==============================================================================
static CApp* emApp;
void one_iter()
{
    SDL_Event Event;
	while(SDL_PollEvent(&Event)) {
		emApp->OnEvent(&Event);
	}

	emApp->OnLoop();
	emApp->OnRender();
}

//==============================================================================
int CApp::OnExecute(int fps) 
{
    if(OnInit() == false) {
        return -1;
    }

	emApp = this;
	
#ifdef EMSCRIPTEN
	emscripten_set_main_loop(one_iter, fps, 1);
#else
	
	const double frame_time = static_cast<double>(CLOCKS_PER_SEC) / fps;
    while(Running)
    {
        double t1 = clock();
        
		one_iter();
        
        int t_left = t1-clock();
        if (t_left<frame_time)
        {
            double ms = 1000 * (frame_time-t_left) / static_cast<double>(CLOCKS_PER_SEC);
            usleep( 1000*ms );
        }
    }
#endif

    OnCleanup();

    return 0;
}

