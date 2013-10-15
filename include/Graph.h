#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "stdafx.h"

class Screen;
class InputMan;

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
    
    void input();
    void zoom_in();
    void zoom_out();
private:    
    int origin[2];
    InputMan* in;
};

#endif
