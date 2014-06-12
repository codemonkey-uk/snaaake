//==============================================================================
#include "CApp.h"
#include <stdio.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

//==============================================================================
CApp::CApp()
	// set up in ::Init
	: mDir( Geometry::uninitialised )
	, mPendingRemove( Geometry::uninitialised )
	, mPaused(false)
{
    Surf_Display = NULL;

    Running = true;
}

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

//------------------------------------------------------------------------------
int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

	emApp = this;
	
#ifdef EMSCRIPTEN
	int fps=24;
	emscripten_set_main_loop(one_iter, fps, 1);
#else
    while(Running) {
		one_iter();
    }
#endif

    OnCleanup();

    return 0;
}

//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;

    return theApp.OnExecute();
}

//==============================================================================
