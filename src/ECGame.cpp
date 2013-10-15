#include "stdafx.h"

int main(int argc, char** argv)
{
    const int FPS = 60, 
              WIDTH = 800, 
              HEIGHT = 600;

    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;
    unsigned int tick = 0;
    int scale = 20;
    
    Screen* screen = new Screen(WIDTH, HEIGHT);
    Random* rand = new Random();
    Graph* graph = new Graph(screen, scale);
        
    int col = 0;

    while(graph->running) {
        screen->clear(~col);

        graph->update();

        tick = SDL_GetTicks();
        SDL_Flip(screen->get_surface());
        if(1000 / FPS > SDL_GetTicks() - tick) {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - tick));
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
