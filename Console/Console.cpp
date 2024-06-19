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

void Console::draw()
{
    if (this->strArr->getLength())
    {
        int A = this->hover ? 255 : 50;
        ctx.CreateDrawZone(this->x, this->y, this->width, this->height);
        ctx.FillRect(this->x, this->y, this->width, this->height, "white", A);
        int x = this->x;
        int y = this->y;
        int index = this->index;
        this->strArr->forEach([x, y, index](saveStr ss, int i)
                              { ctx.DrawText(x + 5, y + i * 15, 15, to_string(ss.index) + ": " + ss.str); });
    }
}

Console::~Console()
{
    delete this->strArr;
    this->strArr = nullptr;
};

Console console(20);
