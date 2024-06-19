#pragma once

#include "../Cell/Cell.cpp"


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
    void draw();
    ~Console();

private:
    bool hover = false;
    int length;
    int x = 10;
    int y = 410;
    int width = 500;
    int height = 180;
    int index = 0;
    void delArr();
};