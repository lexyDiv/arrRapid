#pragma once

class Cell
{
public:
    int x;
    int y;
    int gab;
    Cell();
    Cell(int x, int y, int gab);
    void draw(int index, int ver);
};