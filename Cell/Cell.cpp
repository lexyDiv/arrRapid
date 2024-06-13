#include "Cell.h"
#include "../Context/addContext.cpp"

Cell::Cell(){};

Cell::Cell(int x, int y, int gab)
{
    this->x = x;
    this->y = y;
    this->gab = gab;
};

void Cell::draw(int index, int ver)
{
    if (ver % 5 == 0)
    {
        ctx.FillRect(this->x, this->y, this->gab, this->gab, "black");
    }
    else
    {
        if (index % 3 == 0)
        {
            ctx.FillRect(this->x, this->y, this->gab, this->gab, "white");
        }
        else if(index % 3 == 0)
        {
            ctx.FillRect(this->x, this->y, this->gab, this->gab, "yellow");
        }
        else if(index % 5 == 0)
        {
            ctx.FillRect(this->x, this->y, this->gab, this->gab, "blue");
        }
        else if(index % 7 == 0)
        {
            ctx.FillRect(this->x, this->y, this->gab, this->gab, "violet");
        }
        else
        {
            ctx.FillRect(this->x, this->y, this->gab, this->gab, "green");
        }
    }
};
