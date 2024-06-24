#pragma once

#include "../Sound/Sound.cpp"

class Cell
{
public:
    int x;
    int y;
    int gab;
    Color color;
    Uint8 A = 255;
   // Color col;
   // std::string color33 = "vvvv";
    Cell();
    Cell(int x, int y, int gab, Color color);
    void draw(int index, int ver);
};


