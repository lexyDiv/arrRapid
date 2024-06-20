#include "Console.h"

Console::Console(int length)
{
    this->length = length;
    this->strArr->backForce(length);
}

void Console::delArr()
{
    this->strArr->clear();
    this->strArr->backForce(length);
    this->index = 1;
    this->interval = 0;
}

void Console::clear()
{
    if (this->strArr != nullptr)
    {
        this->delArr();
        this->canClear = false;
    }
}

void Console::log(string str)
{
    if (this->strArr->getLength() == this->length)
    {
        this->strArr->norm();
        this->strArr->shift();
        this->strArr->norm();
        this->strArr->backForce(1);
    }
    saveStr item(str, this->index);
    this->strArr->push(item);
    this->index++;
}

void Console::proc(int mX, int mY, bool pressed)
{

    bool collision = rect_PointCollision({mX, mY}, {this->x, this->y, this->width, this->height});
    this->clearButtonHover = rect_PointCollision({mX, mY},
                                              {this->clearButton.x, this->clearButton.y, this->clearButton.w, this->clearButton.h});
    this->hover = false;

    if (!pressed && this->clickDataStatus)
    {
        this->clickDataStatus = false;
        this->clicked = false;
    }
    if (pressed && !this->clickDataStatus)
    {
        this->clickDataStatus = true;
        this->ClickData = {mX, mY};
        this->clicked = rect_PointCollision(this->ClickData,
                                            {this->x, this->y, this->width - 30, this->height});
        this->canClear = rect_PointCollision(this->ClickData, this->clearButton);
    }
    
    if(this->canClear)
    {
        this->clear();
    }
   

    if ((collision && !this->clickDataStatus) || this->clicked)
    {
        this->hover = true;
    }
    

    if (this->clicked)
    {
        int deltaX = mX - this->saveMouseX;
        int deltaY = mY - this->saveMouseY;
        this->x += deltaX;
        this->y += deltaY;
        this->clearButton = {this->x + 470, this->y, 30, 15};
    }
    this->saveMouseX = mX;
    this->saveMouseY = mY;
    this->procSB();
}

void Console::draw()
{
    int A = this->hover ? 255 : 50;
    if (this->strArr->getLength())
    {
        ctx.CreateDrawZone(this->x, this->y, this->width, this->height);
        ctx.FillRect(this->x, this->y, this->width, this->height, "white", A);
        if (this->clicked)
        {
            ctx.StrokeRect(this->x, this->y, this->width, this->height, "blue");
        }
        int x = this->x;
        int y = this->y;
        int index = this->index;
        int iter = 0;
        int delta = this->strArr->getLength() > 12 ? 12 : this->strArr->getLength();
        for (int i = this->interval; i < this->interval + delta; i++)
        {
            saveStr ss = this->strArr->getItem(i);
            ctx.DrawText(x + 5, y + iter * 15, 15, to_string(ss.index) + ": " + ss.str, A);
            iter++;
        }
        ctx.FillRect(this->clearButton.x, this->clearButton.y, this->clearButton.w, this->clearButton.h, "violet", A - 50);
        ctx.DrawText(this->clearButton.x, this->clearButton.y + 3, 8, "clear");
        if (this->clearButtonHover)
        {
            ctx.StrokeRect(this->clearButton.x, this->clearButton.y, this->clearButton.w, this->clearButton.h, "red");
        }
    }
    if (this->strArr->getLength() > 12)
    {
        this->drawSB(A);
    }
}

void Console::drawSB(int A)
{
    ctx.StrokeRect(
        this->scrollBar.x,
        this->scrollBar.y,
        this->scrollBar.w,
        this->scrollBar.h,
        "violet", A);
    ctx.StrokeRect(this->scrollRunner.x,
                   this->scrollRunner.y,
                   this->scrollRunner.w,
                   this->scrollRunner.h,
                   "blue",
                   A);
    ctx.DrawImage(this->runner,
                  0,
                  0,
                  512,
                  512,
                  this->scrollRunner.x,
                  this->scrollRunner.y,
                  this->scrollRunner.w,
                  this->scrollRunner.h,
                  SDL_FLIP_NONE, 0, A);
}

void Console::procSB()
{
    scrollBar = {this->x + 470, this->y + 15, 30, 165};
    scrollRunner = {this->x + 470, this->y + 15 + this->scrollRunnerIndex, 30, 165};
    int l = this->strArr->getLength();

    if(!this->stopAutoScroll && l > 12)
    {
        this->interval = l - 12;
    }
    else if(this->interval + 12 == l && this->stopAutoScroll > 0)
    {
       // this->log("this is dno");
       this->stopAutoScroll--;
    }
}

void Console::whellOrder(int vector)
{
    int l = this->strArr->getLength();
    if (l > 12 && this->hover)
    {
        if (vector > 0 && this->interval)
        {
            this->interval--;
            this->stopAutoScroll = 5;
        }
        else if (vector < 0 && this->interval + 12 < l)
        {
            this->interval++;
        }
    }
    else
    {
        this->interval = 0;
    }
}

Console::~Console()
{
    delete this->strArr;
    this->strArr = nullptr;
};

Console console(2000);
