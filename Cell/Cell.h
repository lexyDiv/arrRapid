#pragma once

#include "../Context/Context.cpp"

class Cell
{
public:
    int x;
    int y;
    int gab;
    std::string color;
   // Color col;
   // std::string color33 = "vvvv";
    Cell();
    Cell(int x, int y, int gab, std::string color);
    void draw(int index, int ver);
};


