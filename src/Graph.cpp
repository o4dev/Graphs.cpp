#include "Graph.h"

const int BLACK = 0x00;

Graph::Graph(Screen* s, int sca) 
{
    screen = s;
    scale = sca;
    
    width = s->width;
    height = s->height;

    origin[0] = width/2;
    origin[1] = height/2;

    in = new InputMan();

    running = true;
}

Graph::~Graph(void)
{
}

int units(){[1]
    return {(origin[0]/scale), (origin[1]/scale)};
}


int (*to_graph(int x, int y))[1]
{
    return *{origin[0]+(x*units()[0]), origin[1]-(y*units()[1])}
}

int (*from_graph(int x, int y))[1]
{
    return *{((x-origin[0])/units[0]), -((origin[1]-y)/units[1])}
}


void Graph::update()
{
    input();

    draw_axis();
    for (int i = 0; i < origin[0]; ++i)
    {
        if ((i % scale) == 0)
        {

            // x = 0, y > 0
            screen->set_pixel(origin[0] + 2, origin[1] - i, BLACK);
            screen->set_pixel(origin[0] + 1, origin[1] - i, BLACK);
            screen->set_pixel(origin[0] - 1, origin[1] - i, BLACK);
            screen->set_pixel(origin[0] - 2, origin[1] - i, BLACK);

            // x = 0, y < 0
            screen->set_pixel(origin[0] + 2, i + origin[1], BLACK);
            screen->set_pixel(origin[0] + 1, i + origin[1], BLACK);
            screen->set_pixel(origin[0] - 1, i + origin[1], BLACK);
            screen->set_pixel(origin[0] - 2, i + origin[1], BLACK);

            // y = 0, x > 0
            screen->set_pixel(origin[0] - i, origin[1] + 2, BLACK);
            screen->set_pixel(origin[0] - i, origin[1] + 1, BLACK);
            screen->set_pixel(origin[0] - i, origin[1] - 1, BLACK);
            screen->set_pixel(origin[0] - i, origin[1] - 2, BLACK);

            // y = 0, x < 0
            screen->set_pixel(i + origin[0], origin[1] + 2, BLACK);
            screen->set_pixel(i + origin[0], origin[1] + 1, BLACK);
            screen->set_pixel(i + origin[0], origin[1] - 1, BLACK);
            screen->set_pixel(i + origin[0], origin[1] - 2, BLACK);
        }
    }
}

void Graph::draw_axis()
{
    screen->draw_line(origin[0], 0, origin[0], height, BLACK);
    screen->draw_line(0, origin[1], width, origin[1], BLACK);
}


void Graph::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
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
        running = false;
    if (in->get_key(SDLK_MINUS))
        zoom_out();
    if (in->get_key(SDLK_EQUALS))
        zoom_in();
}


void Graph::zoom_in()
{
    if (scale < origin[0])
        scale += 1;
}


void Graph::zoom_out()
{
    if (scale > 2)
        scale -= 1;
}


