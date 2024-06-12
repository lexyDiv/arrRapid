#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "../Image/Image.cpp"

struct Color
{
    int R;
    int G;
    int B;
};



class Context
{
public:
    Context(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    Color ColorsMap(std::string color);
    void Close();
    void ClearRect();
    void ClearRect(int x, int y, int width, int height);
    void End();
    SDL_Renderer *getRenderer();
    void FillRect(int x, int y, int width, int height, int R, int G, int B, int A);
    void FillRect(int x, int y, int width, int height, int R, int G, int B);
    void FillRect(int x, int y, int width, int height, std::string color);
    void FillRect(int x, int y, int width, int height);
    void FillRect(int x, int y, int width, int height, std::string color, int A);
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
    void DrawImage(Image *image,
                   int animX,
                   int animY,
                   int animW,
                   int animH,
                   int x,
                   int y,
                   int width,
                   int height,
                   SDL_RendererFlip flip);
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
                   double conor);
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
                   int alpha);
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
                   int rotY);
    ~Context();

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
};