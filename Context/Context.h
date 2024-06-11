#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "../Image/Image.cpp"

class Context
{
public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    Context(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void Close();
    void ClearRect();
    void End();
    void DrawImage(Image &image,
                   int animX,
                   int animY,
                   int animW,
                   int animH,
                   int x,
                   int y,
                   int width,
                   int height,
                   double conor, 
                   SDL_RendererFlip flip);
};