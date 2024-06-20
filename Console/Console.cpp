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
    this->index = 0;
}

void Console::clear()
{
    if (this->strArr != nullptr)
    {
        this->delArr();
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
    if (!this->canClick && pressed)
    {
        this->canClick = 1;
        if (collision)
        {
            this->canClick = 2;
        }
    }

    if (!pressed)
    {
        this->clicked = false;
        this->canClear = true;
        this->canClick = 0;
    }
    this->clearButtonHover = false;
    if (!this->clicked)
    {
        this->hover = false;
    }
    if (collision)
    {
        this->hover = true;

        if (pressed && this->canClick == 2)
        {
            this->clicked = true;
        }
    }
    if (rect_PointCollision({mX, mY}, {this->clearButton.x, this->clearButton.y,
                                       this->clearButton.w, this->clearButton.h}))
    {
        this->clearButtonHover = true;
        this->clicked = false;
        if (this->canClear && pressed && this->canClick == 2)
        {
            this->canClear = false;
            this->clear();
        }
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
}

void Console::draw()
{
    if (this->strArr->getLength())
    {
        int A = this->hover ? 255 : 50;
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
            ctx.DrawText(x + 5, y + iter * 15, 15, to_string(ss.index) + ": " + ss.str);
            iter++;
        }
        ctx.FillRect(this->clearButton.x, this->clearButton.y, this->clearButton.w, this->clearButton.h, "violet", A - 50);
        ctx.DrawText(this->clearButton.x, this->clearButton.y + 3, 8, "clear");
        if (this->clearButtonHover)
        {
            ctx.StrokeRect(this->clearButton.x, this->clearButton.y, this->clearButton.w, this->clearButton.h, "red");
        }
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

Console console(200);
