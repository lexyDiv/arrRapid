#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "../Image/Image.cpp"

class Context
{
public:
    Context(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void Close();
    void ClearRect();
    void ClearRect(int x, int y, int width, int height);
    void End();
    SDL_Renderer *getRenderer();
    void DrawImage(Image *image,
                   int animX,
                   int animY,
                   int animW,
                   int animH,
                   int x,
                   int y,
                   int width,
                   int height,
                   SDL_RendererFlip flip,
                   double conor,
                   int alpha,
                   int rotX,
                   int rotY,
                   int R,
                   int G,
                   int B);
    void DrawImage(Image *image,
                   int animX,
                   int animY,
                   int animW,
                   int animH,
                   int x,
                   int y,
                   int width,
                   int height);
    ~Context();

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
};