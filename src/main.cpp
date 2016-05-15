#include "snaaake.h"
#include <SDL/SDL.h>

// terrible hacks,
#ifdef EMSCRIPTEN
// the html container handles starting the music
inline void PlayMusic(){}
#else
// Objective C code for starting the music on os x
extern "C" void PlayMusic();
#endif

int main(int argc, char* argv[]) 
{
    SnakeApp theApp;

    PlayMusic();
    
    return theApp.OnExecute(24);
}