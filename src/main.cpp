#include "SDL/SDL.h"
#include "c_types.h"
#include "Screen.h"
#include "Graph.h"

using namespace std;

int main(int argc, char** argv)
{
    const int FPS = 60, 
              WIDTH = 800, 
              HEIGHT = 600,
              SCALE = 20;

    SDL_Init(SDL_INIT_EVERYTHING);
    uint tick = 0;
    
    Screen* screen = new Screen(WIDTH, HEIGHT);
    Graph* graph = new Graph(screen, SCALE);

    while(graph->running)
    {
        screen->clear(~0);

        graph->update();

        tick = SDL_GetTicks();
        SDL_Flip(screen->get_surface());
        if(1000 / FPS > SDL_GetTicks() - tick)
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
