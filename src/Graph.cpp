#include "Graph.h"

const int BLACK = 0x000000;
const int RED = 0xFF0000;

Graph::Graph(Screen* s, int sca) 
{
    screen = s;
    scale = sca;
    
    size = s->width;
    s->height = size;

    origin = size/2;

    in = new InputMan();

    running = true;
}

Graph::~Graph(void)
{
    //
    //
}

void Graph::update()
{
    input();
    draw_axis();

    // Let's plot some points !
    set_point(2, 3);
}

void Graph::draw_axis()
{
    screen->draw_line(origin, 0, origin, size, BLACK);
    screen->draw_line(0, origin, size, origin, BLACK);

    draw_scale();
}

void Graph::draw_scale()
{
    int n = size / (2 * scale);
    for (int i = 0; i < scale; ++i)
    {
        // x = 0, y > 0
        screen->set_pixel(origin + 2, origin - i * n, BLACK);
        screen->set_pixel(origin + 1, origin - i * n, BLACK);
        screen->set_pixel(origin - 1, origin - i * n, BLACK);
        screen->set_pixel(origin - 2, origin - i * n, BLACK);

        // x = 0, y < 0
        screen->set_pixel(origin + 2, origin + i * n, BLACK);
        screen->set_pixel(origin + 1, origin + i * n, BLACK);
        screen->set_pixel(origin - 1, origin + i * n, BLACK);
        screen->set_pixel(origin - 2, origin + i * n, BLACK);

        // y = 0, x > 0
        screen->set_pixel( origin - i * n, origin + 2, BLACK);
        screen->set_pixel( origin - i * n, origin + 1, BLACK);
        screen->set_pixel( origin - i * n, origin - 1, BLACK);
        screen->set_pixel( origin - i * n, origin - 2, BLACK);

        // y = 0, x < 0
        screen->set_pixel( origin + i * n, origin + 2, BLACK);
        screen->set_pixel( origin + i * n, origin + 1, BLACK);
        screen->set_pixel( origin + i * n, origin - 1, BLACK);
        screen->set_pixel( origin + i * n, origin - 2, BLACK);
    }
}

void Graph::set_point(int x, int y)
{
    int n = size / (2 * scale);
    int xVal = origin + (x * n);
    int yVal = origin - (y * n);

    // Making the cross

    // center
    screen->set_pixel(xVal, yVal, RED);
    screen->set_pixel(xVal, yVal, RED);
    screen->set_pixel(xVal, yVal, RED);
    screen->set_pixel(xVal, yVal, RED);
    // up
    screen->set_pixel(xVal, yVal+2, RED);
    screen->set_pixel(xVal, yVal+1, RED);
    // down
    screen->set_pixel(xVal, yVal-1, RED);
    screen->set_pixel(xVal, yVal-2, RED);
    // left
    screen->set_pixel(xVal-2, yVal, RED);
    screen->set_pixel(xVal-1, yVal, RED);
    // right
    screen->set_pixel(xVal+1, yVal, RED);
    screen->set_pixel(xVal+2, yVal, RED);
}



void Graph::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                in->set_key_down(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                in->set_key_up(event.key.keysym.sym);
                break;
        }
    }

    if (in->get_key(SDLK_ESCAPE))
    {
        running = false;
    }
    if (in->get_key(SDLK_MINUS))
    {
        zoom_out();
    }
    if (in->get_key(SDLK_EQUALS))
    {
        zoom_in();
    }
}


void Graph::zoom_in()
{
    if (scale > 2)
    {
        scale -= 1;
    }
}


void Graph::zoom_out()
{
    if (scale < origin)
    {
        scale += 1;
    }
}


