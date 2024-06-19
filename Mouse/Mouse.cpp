#include "Mouse.h"

void Mouse::move(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Mouse::pressKey(int keyCode)
{
    switch (keyCode)
    {
    case 1:
    {
        this->leftKey = true;
        break;
    }
    case 2:
    {
        this->midKey = true;
        break;
    }
    case 3:
    {
        this->rightKey = true;
        break;
    }
    }
}

void Mouse::upKey(int keyCode)
{
    switch (keyCode)
    {
    case 1:
    {
        this->leftKey = false;
        break;
    }
    case 2:
    {
        this->midKey = false;
        break;
    }
    case 3:
    {
        this->rightKey = false;
        break;
    }
    }
}

Mouse mouse;
