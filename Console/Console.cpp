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
        this->isBlocked = false;
    }
}

void Console::log(string str)
{
    int l = this->strArr->getLength();
    if (l == this->length - 1)
    {
        str = "Click clear button to continue.";
        this->isBlocked = true;
    }
    if (l < this->length)
    {
        saveStr item(str, this->index);
        this->strArr->push(item);
        this->index++;
    }
}

void Console::proc(int mX, int mY, bool pressed)
{
    bool collision = rect_PointCollision({mX, mY}, {this->x, this->y, this->width, this->height});
    this->clearButtonHover = rect_PointCollision({mX, mY},
                                                 {this->clearButton.x,
                                                  this->clearButton.y,
                                                  this->clearButton.w,
                                                  this->clearButton.h});

    this->hover = false;

    if (!pressed && this->clickDataStatus)
    {
        this->clickDataStatus = false;
        this->clicked = false;
        this->clickRunnerZone = false;
        this->runnerTake = false;
    }
    if (pressed && !this->clickDataStatus)
    {
        this->clickDataStatus = true;
        this->ClickData = {mX, mY};
        this->clicked = rect_PointCollision(this->ClickData,
                                            {this->x, this->y, this->width - 30, this->height});
        this->canClear = rect_PointCollision(this->ClickData, this->clearButton);
        this->clickRunnerZone = rect_PointCollision(this->ClickData, this->scrollBar);
        this->runnerTake = rect_PointCollision({mX, mY},
                                               {this->scrollBar.x,
                                                this->scrollBar.y,
                                                this->scrollBar.w,
                                                this->scrollBar.h});
        if (this->runnerTake)
        {
            this->stopAutoScroll = 1;
        }
    }

    this->runnerHover = ((collision && !this->clickDataStatus) &&
                             rect_PointCollision({mX, mY},
                                                 {this->scrollBar.x,
                                                  this->scrollBar.y,
                                                  this->scrollBar.w,
                                                  this->scrollBar.h}) ||
                         this->runnerTake);

    if (this->canClear)
    {
        this->clear();
    }

    if ((collision && !this->clickDataStatus) || this->clicked || this->clickRunnerZone)
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
    if (this->strArr->getLength() >= 12)
    {
        this->procSB();
        this->procRunner(mX, mY);
    };
}

void Console::draw()
{
    int A = this->hover ? 255 : 50;
    int A2 = this->hover ? 150 : 50;
    if (this->strArr->getLength())
    {

        int l = this->strArr->getLength();
        if (l >= 12)
        {
            if (this->interval < 0)
            {
                this->interval = 0;
            }
            else if (this->interval > l - 12)
            {
                this->interval = l - 12;
            }
        }

        ctx.CreateDrawZone(this->x, this->y, this->width, this->height);

        ctx.FillRect(this->x, this->y, this->width, this->height, "white", A);
        if (this->clicked)
        {
            ctx.StrokeRect(this->x, this->y, this->width, this->height, "blue");
        }
        if (this->isBlocked)
        {
            ctx.FillRect(this->x, this->y, this->width, this->height, "red", 50);
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
        this->scrollBar = {this->x + 470, this->y + 15, 30, 165};
        ctx.FillRect(this->scrollBar.x,
                     this->y,
                     this->scrollBar.w,
                     this->height,
                     "white",
                     A);
        ctx.FillRect(this->clearButton.x,
                     this->clearButton.y,
                     this->clearButton.w,
                     this->clearButton.h,
                     "violet",
                     A2);
        ctx.DrawText(this->clearButton.x, this->clearButton.y + 3, 8, "clear", A);
        if (this->clearButtonHover)
        {
            ctx.StrokeRect(this->clearButton.x,
                           this->clearButton.y,
                           this->clearButton.w,
                           this->clearButton.h,
                           "red");
        }
        if (this->strArr->getLength() >= 12)
        {
            this->drawSB(A);
        }
        else
        {
            this->scrollBar = {this->x + 470, this->y + 15, 30, 165};
            ctx.FillRect(this->scrollBar.x,
                         this->scrollBar.y,
                         this->scrollBar.w,
                         this->scrollBar.h,
                         "black",
                         30);
        }
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
                   this->scrollRunnerDrawY,
                   this->scrollRunner.w,
                   this->scrollRunner.h,
                   "blue",
                   A);
    if (this->runnerHover)
    {
        ctx.FillRect(this->scrollRunner.x,
                     this->scrollRunnerDrawY,
                     this->scrollRunner.w,
                     this->scrollRunner.h, "blue", 50);
    }
    ctx.DrawImage(this->runner,
                  0,
                  0,
                  512,
                  512,
                  this->scrollRunner.x,
                  this->scrollRunnerDrawY,
                  this->scrollRunner.w,
                  this->scrollRunner.h,
                  SDL_FLIP_NONE, 0, A);

    ctx.DrawLine({this->scrollRunner.x, this->scrollRunner.y},
                 {this->scrollRunner.x + 30, this->scrollRunner.y}, "red");
}

void Console::procSB()
{
    scrollBar = {this->x + 470, this->y + 15, 30, 165};
    int l = this->strArr->getLength();
    int h;
    h = (12 * 165) / l;
    h = h > 20 ? h : 20;

    this->scrollRunner.h = h;
    this->scrollRunner.x = this->x + 470;

    if (!this->stopAutoScroll && l > 12)
    {
        this->interval = l - 12;
    }
    else if (this->interval + 12 == l && this->stopAutoScroll > 0)
    {
        this->stopAutoScroll--;
    }
}

void Console::procRunner(int mX, int mY)
{
    int l = this->strArr->getLength();

    if (this->runnerTake)
    {
        this->stopAutoScroll = 1;
        int deltaY = mY - this->scrollBar.y;
        this->interval = (deltaY * (l - 11)) / 165;

        if (this->interval < 0)
        {
            this->interval = 0;
        }
    }

    float zoneNum = l - 11;
    float zoneSize = 165 / zoneNum;
    float dY = (this->interval * zoneSize) + zoneSize / 2;

    this->scrollRunner.y = this->y + 15 + dY;
    this->scrollRunnerDrawY = this->scrollRunner.y - this->scrollRunner.h / 2;

    if (this->scrollRunnerDrawY < this->scrollBar.y)
    {
        this->scrollRunnerDrawY = this->scrollBar.y;
    }
    else if (this->scrollRunnerDrawY + this->scrollRunner.h > this->scrollBar.y + this->scrollBar.h)
    {
        this->scrollRunnerDrawY = (this->scrollBar.y + this->scrollBar.h) - this->scrollRunner.h;
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
            this->stopAutoScroll = 1;
        }
        else if (vector < 0 && this->interval + 12 < l)
        {
            this->interval++;
        }
    }
}

Console::~Console()
{
    delete this->strArr;
    this->strArr = nullptr;
};

Console console(1000);
