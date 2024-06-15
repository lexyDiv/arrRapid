#pragma once

#include "../Context/Context.cpp"

class Cell
{
public:
    int x;
    int y;
    int gab;
    Color color;
   // Color col;
   // std::string color33 = "vvvv";
    Cell();
    Cell(int x, int y, int gab, Color color);
    void draw(int index, int ver);
};


