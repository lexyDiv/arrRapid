#pragma once

#include "../Context/Context.cpp"

class saveStr
{
public:
    string str;
    int index;
    saveStr(){};
    saveStr(string str, int index)
    {
        this->str = str;
        this->index = index;
    };
};

class Console
{
public:
    rapid<saveStr> *strArr = new rapid<saveStr>;
    Console(int length);
    void clear();
    void log(string str);
    void proc(int mX, int mY, bool pressed);
    void draw();
    ~Console();

private:
    bool hover = false;
    bool clicked = false;
    int length;
    int x = 10;
    int y = 410;
    SDL_Rect clearButton = {this->x + 470, this->y, 30, 15};
    bool clearButtonHover = false;
    int saveMouseX = 0;
    int saveMouseY = 0;
    int width = 500;
    int height = 180;
    int index = 0;
    bool canClear = true;
    int canClick = 0;
    void delArr();
};

bool rect_PointCollision(Point p, SDL_Rect r)
{
    if (!(p.x < r.x || p.x > r.x + r.w || p.y < r.y || p.y > r.y + r.h))
    {
        return true;
    }
    return false;
}