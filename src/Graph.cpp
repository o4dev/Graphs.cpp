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

void Graph::update()
{
    input();
    draw_axis();

    // Let's plot some points !
    screen->set_pixel(to_graph_x(2), to_graph_y(3), BLACK);
}

void Graph::draw_axis()
{
    screen->draw_line(origin[0], 0, origin[0], height, BLACK);
    screen->draw_line(0, origin[1], width, origin[1], BLACK);

    draw_scale();
}

void Graph::draw_scale()
{
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


int Graph::units_x(){
    return origin[0]/scale;
}
int Graph::units_y(){
    return origin[1]/scale;
}

int Graph::to_graph_x(int x)
{
    return origin[0]+(x*units_x());;
}
int Graph::to_graph_y(int y)
{
    return origin[1]-(y*units_y());
}

int Graph::from_graph_x(int x)
{
    return (x-origin[0])/units_x();
}
int Graph::from_graph_y(int y)
{
    return -((origin[1]-y)/units_y());
}
