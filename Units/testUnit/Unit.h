#pragma once
#include "../../LTexture/LTexture.h"

// 1536 256


class Unit
{
public:
    int x;
    int y;
    int conor;
    int alpha;
    int animX = 0;
    int animY = 0;
    int animStepX = 1536 / 6;
    int animStepY = 256;
    int gabX;
    int gabY;
    LTexture* texture;
    Unit();
    Unit(int x,
         int y,
         int conor,
         int alpha,
         int gabX,
         int gabY,
         LTexture* texture);
         void draw(SDL_Renderer *gRenderer);
   // ~Unit();
};


