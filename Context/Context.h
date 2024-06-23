#pragma once

#include "../Image/Image.cpp"



struct Color
{
    int R;
    int G;
    int B;
};

struct Point
{
    int x;
    int y;
};

class Context
{
public:
    SDL_PixelFormat *pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    SDL_Window *gWindow = nullptr;
    Context(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    Color ColorsMap(std::string color);
    void Close();
    void ClearRect();
    void ClearRect(int x, int y, int width, int height);
    void End();
    SDL_Renderer *getRenderer();
    void getFont();

    void DrawText(int x, int y, int size, string str);
    void DrawText(int x, int y, int size, string str, int A);

    void CreateDrawZone(int x, int y, int width, int height);

    void DrawLine(Point start, Point finish, int R, int G, int B, int A);
    void DrawLine(Point start, Point finish, int R, int G, int B);
    void DrawLine(Point start, Point finish, string color, int A);
    void DrawLine(Point start, Point finish, string color);
    void DrawLine(Point start, Point finish);
    void DrawHendleFigure(Point arrPoints[], Point rotPoint, int length, float conor, string color);

    void FillRect(int x, int y, int width, int height, int R, int G, int B, int A);
    void FillRect(int x, int y, int width, int height, int R, int G, int B);
    void FillRect(int x, int y, int width, int height, std::string color, int A);
    void FillRect(int x, int y, int width, int height, std::string color);
    void FillRect(int x, int y, int width, int height);

    void StrokeRect(int x, int y, int width, int height, int R, int G, int B, int A);
    void StrokeRect(int x, int y, int width, int height, int R, int G, int B);
    void StrokeRect(int x, int y, int width, int height, std::string color, int A);
    void StrokeRect(int x, int y, int width, int height, std::string color);
    void StrokeRect(int x, int y, int width, int height);

    void PixelHendler(Image *image,
                      int x,
                      int y,
                      int width,
                      int height,
                      function<void(Uint32 *pixelsArr, SDL_PixelFormat *pixelFormat)> fn);
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

    class conorDelta
    {
    public:
        float conor;
        float delta;
    };
    ~Context();

public:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    void *mRawPixels = nullptr;
    int mRawPitch = 0;
    SDL_Renderer *gRenderer = nullptr;
    Image * font = nullptr;
};