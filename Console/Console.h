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
    void drawSB(int A);
    void procSB();
    void procRunner(int mX, int mY);
    void whellOrder(int vector);
    ~Console();

private:
    bool hover = false;
    bool clicked = false;
    int length;
    int x = 10;
    int y = 410;
    SDL_Rect clearButton = {this->x + 470, this->y, 30, 15};
    SDL_Rect scrollBar = {this->x + 470, this->y + 15, 30, 165};
    SDL_Rect scrollRunner = {this->x + 470, this->y + 15, 30, 30};
    int scrollRunnerDrawY = 0;
    int stopAutoScroll = 0;
    Point ClickData = {-1, -1};
    bool clickDataStatus = false;
    Image *runner = new Image("src/runner.png");
    bool clickRunnerZone = false;
    bool clearButtonHover = false;
    bool runnerHover = false;
    bool runnerTake = false;
    Point runnerTakePoint = {-1, -1};
    int saveMouseX = 0;
    int saveMouseY = 0;
    int width = 500;
    int height = 180;
    int index = 1;
    bool canClear = false;
    int interval = 0;
    bool isBlocked = false;
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