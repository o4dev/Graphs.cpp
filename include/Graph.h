#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "Screen.h"
#include "InputMan.h"
#include "Point.h"

class Graph
{
public:
    int size;
    int scale;
    Screen* screen;

    Graph(Screen* s, int sca); 
    ~Graph(void);

    bool running;

    void update();
    void draw_axis();
    void draw_scale();

    void set_point(int x, int y);
    
    void input();
    void zoom_in();
    void zoom_out();
private:    
    int origin;
    InputMan* in;
};

#endif
