#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "Screen.h"
#include "InputMan.h"

class Graph
{
public:
    int width, height;
    int scale;
    Screen* screen;

    Graph(Screen* s, int sca); 
    ~Graph(void);

    bool running;

    void update();
    void draw_axis();
    void draw_scale();
    
    void input();
    void zoom_in();
    void zoom_out();

    int units_x();
    int units_y();
    int to_graph_x(int x);
    int to_graph_y(int y);
    int from_graph_x(int x);
    int from_graph_y(int y);
private:    
    int origin[2];
    InputMan* in;
};

#endif
