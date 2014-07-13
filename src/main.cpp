#include "snaaake.h"
#include <SDL/SDL.h>

int main(int argc, char* argv[]) 
{
    SnakeApp theApp;

    return theApp.OnExecute(24);
}