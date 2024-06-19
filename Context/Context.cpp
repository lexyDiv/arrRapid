#include "Context.h"

Context::Context(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    this->SCREEN_WIDTH = SCREEN_WIDTH;
    this->SCREEN_HEIGHT = SCREEN_HEIGHT;

    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window SDL_WINDOW_FULLSCREEN  SDL_WINDOW_OPENGL
        this->gWindow = SDL_CreateWindow("SDL Tutorial",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         this->SCREEN_WIDTH,
                                         this->SCREEN_HEIGHT,
                                         SDL_WINDOW_OPENGL
                                          // | SDL_WINDOW_FULLSCREEN
        );
        if (this->gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create vsynced renderer for window
            this->gRenderer = SDL_CreateRenderer(this->gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (this->gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                // SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    if (!success)
    {
        this->Close();
        printf("this is pisya");
    };
}

Color Context::ColorsMap(std::string color)
{
    if (color == "red")
    {
        return {255, 0, 0};
    }
    else if (color == "orange")
    {
        return {255, 165, 0};
    }
    else if (color == "yellow")
    {
        return {255, 255, 0};
    }
    else if (color == "green")
    {
        return {0, 128, 0};
    }
    else if (color == "blue")
    {
        return {0, 0, 255};
    }
    else if (color == "violet")
    {
        return {127, 0, 255};
    }
    else if (color == "white")
    {
        return {255, 255, 255};
    }
    else if (color == "black")
    {
        return {0, 0, 0};
    }
    else if (color == "dgreen")
    {
        return {0, 100, 0};
    }
    return {0, 0, 0};
}

void Context::Close()
{
    try
    {
        SDL_DestroyRenderer(this->gRenderer);
        SDL_DestroyWindow(this->gWindow);
        this->gWindow = NULL;
        this->gRenderer = NULL;

        mRawPixels = nullptr;
        delete pixelFormat;
        pixelFormat = nullptr;

        IMG_Quit();
        SDL_Quit();
    }
    catch (const std::exception &e)
    {
        printf("delete is faled!");
    }
    printf(" all deleted ");
}

void Context::ClearRect()
{
    SDL_SetRenderDrawColor(this->gRenderer, 255, 255, 255, 255);
    SDL_Rect rect = {0, 0, this->SCREEN_WIDTH, this->SCREEN_HEIGHT};
    SDL_RenderFillRect(this->gRenderer, &rect);
}

void Context::ClearRect(int x, int y, int width, int height)
{
    SDL_SetRenderDrawColor(this->gRenderer, 255, 255, 255, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(this->gRenderer, &rect);
}

void Context::End()
{
    SDL_RenderPresent(this->gRenderer);
}

SDL_Renderer *Context::getRenderer()
{
    return this->gRenderer;
}

void Context::getFont()
{
    this->font = new Image("src/literas_1.png");
}

void Context::DrawText(int x, int y, int size, string str)
{
    int drawX = x;
    for (int i = 0; i < str.size(); i++)
    {
        char litera = str[i];
        int animX = ((int)litera - 33) * 20;
        this->DrawImage(this->font, animX, 0, 20, 20, drawX, y, size, size);
        drawX += size * 0.75;
    }
}

void Context::CreateDrawZone(int x, int y, int width, int height)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.h = height;
    rect.w = width;
    SDL_RenderSetClipRect(this->gRenderer,
                          &rect);
}

void Context::DrawLine(Point start, Point finish, int R, int G, int B, int A)
{
    SDL_SetRenderDrawBlendMode(this->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(this->getRenderer(), R, G, B, A);
    SDL_RenderDrawLine(this->gRenderer, start.x, start.y, finish.x, finish.y);
}

void Context::DrawLine(Point start, Point finish, int R, int G, int B)
{
    SDL_SetRenderDrawColor(this->getRenderer(), R, G, B, 255);
    SDL_RenderDrawLine(this->gRenderer, start.x, start.y, finish.x, finish.y);
}

void Context::DrawLine(Point start, Point finish, string color, int A)
{
    Color c = this->ColorsMap(color);
    SDL_SetRenderDrawColor(this->getRenderer(), c.R, c.G, c.B, A);
    SDL_RenderDrawLine(this->gRenderer, start.x, start.y, finish.x, finish.y);
}

void Context::DrawLine(Point start, Point finish, string color)
{
    Color c = this->ColorsMap(color);
    SDL_SetRenderDrawColor(this->getRenderer(), c.R, c.G, c.B, 255);
    SDL_RenderDrawLine(this->gRenderer, start.x, start.y, finish.x, finish.y);
}

void Context::DrawLine(Point start, Point finish)
{
    SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
    SDL_RenderDrawLine(this->gRenderer, start.x, start.y, finish.x, finish.y);
}

void Context::DrawHendleFigure(Point arrPoints[], Point rotPoint, int length, float conor, string color)
{
    Point points[length];
    double rad = conor * (M_PI / 180);
    for (int i = 0; i < length; i++)
    {
        Point point = arrPoints[i];
        float deltaX = rotPoint.x - point.x;
        float deltaY = rotPoint.y - point.y;
        float delta = sqrt(deltaX * deltaX + deltaY * deltaY);
        float conorData = atan2(deltaY, deltaX);
        int x = rotPoint.x + cos(conorData + rad) * -delta;
        int y = rotPoint.y + sin(conorData + rad) * -delta;
        Point pointData = {x, y};
        points[i] = pointData;
    }

    for (int i = 0; i < length; i++)
    {
        Point point1 = points[i];
        Point point2 = i < length - 1 ? points[i + 1] : points[0];
        this->DrawLine(point1, point2, color);
    }
}

void Context::FillRect(int x, int y, int width, int height, int R, int G, int B, int A)
{
    SDL_SetRenderDrawBlendMode(this->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(this->getRenderer(), R, G, B, A);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(this->getRenderer(), &rect);
}

void Context::FillRect(int x, int y, int width, int height, int R, int G, int B)
{
    SDL_SetRenderDrawColor(this->getRenderer(), R, G, B, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(this->getRenderer(), &rect);
}

void Context::FillRect(int x, int y, int width, int height, std::string color)
{
    Color c = this->ColorsMap(color);
    SDL_SetRenderDrawColor(this->getRenderer(), c.R, c.G, c.B, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(this->getRenderer(), &rect);
}

void Context::FillRect(int x, int y, int width, int height)
{
    SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(this->getRenderer(), &rect);
}

void Context::FillRect(int x, int y, int width, int height, std::string color, int A)
{
    Color c = this->ColorsMap(color);
    SDL_SetRenderDrawBlendMode(this->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(this->getRenderer(), c.R, c.G, c.B, A);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(this->getRenderer(), &rect);
}

void Context::StrokeRect(int x, int y, int width, int height, int R, int G, int B, int A)
{
    SDL_SetRenderDrawBlendMode(this->getRenderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(this->getRenderer(), R, G, B, A);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(this->gRenderer, &rect);
}

void Context::StrokeRect(int x, int y, int width, int height, int R, int G, int B)
{
    SDL_SetRenderDrawColor(this->getRenderer(), R, G, B, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(this->gRenderer, &rect);
}

void Context::StrokeRect(int x, int y, int width, int height, std::string color, int A)
{
    Color c = this->ColorsMap(color);
    SDL_SetRenderDrawColor(this->getRenderer(), c.R, c.G, c.B, A);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(this->gRenderer, &rect);
}

void Context::StrokeRect(int x, int y, int width, int height, std::string color)
{
    Color c = this->ColorsMap(color);
    SDL_SetRenderDrawColor(this->getRenderer(), c.R, c.G, c.B, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(this->gRenderer, &rect);
}

void Context::StrokeRect(int x, int y, int width, int height)
{
    SDL_SetRenderDrawColor(this->getRenderer(), 0, 0, 0, 255);
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(this->gRenderer, &rect);
}

void Context::PixelHendler(Image *image,
                           int x,
                           int y,
                           int width,
                           int height,
                           function<void(Uint32 *pixelsArr, SDL_PixelFormat *pixelFormat)> fn)
{
    SDL_Rect rect{x, y, width, height};
    // void *mRawPixels;
    // int mRawPitch;
    SDL_LockTexture(image->mTexture, &rect, &this->mRawPixels, &this->mRawPitch);
    Uint32 *pixelsArr = (Uint32 *)this->mRawPixels;

    fn(pixelsArr, this->pixelFormat);

    SDL_UnlockTexture(image->mTexture);
    this->mRawPixels = NULL;
    this->mRawPitch = 0;
}

void Context::DrawImage(Image *image,
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
                        int B)
{
    SDL_Rect anim{animX, animY, animW, animH};
    SDL_Rect pos{x, y, width, height};
    SDL_Point center{rotX, rotY};

    SDL_SetTextureAlphaMod(image->mTexture, alpha);
    SDL_SetTextureColorMod(image->mTexture, R, G, B);
    SDL_RenderCopyEx(this->gRenderer, image->mTexture, &anim, &pos, conor, &center, flip);
    SDL_SetTextureAlphaMod(image->mTexture, 255);
    SDL_SetTextureColorMod(image->mTexture, 255, 255, 255);
}

void Context::DrawImage(Image *image,
                        int animX,
                        int animY,
                        int animW,
                        int animH,
                        int x,
                        int y,
                        int width,
                        int height)
{
    SDL_Rect anim{animX, animY, animW, animH};
    SDL_Rect pos{x, y, width, height};

    SDL_RenderCopyEx(this->gRenderer, image->mTexture, &anim, &pos, 0, NULL, SDL_FLIP_NONE);
}

void Context::DrawImage(Image *image,
                        int animX,
                        int animY,
                        int animW,
                        int animH,
                        int x,
                        int y,
                        int width,
                        int height,
                        SDL_RendererFlip flip)
{
    SDL_Rect anim{animX, animY, animW, animH};
    SDL_Rect pos{x, y, width, height};

    SDL_RenderCopyEx(this->gRenderer, image->mTexture, &anim, &pos, 0, NULL, flip);
}

void Context::DrawImage(Image *image,
                        int animX,
                        int animY,
                        int animW,
                        int animH,
                        int x,
                        int y,
                        int width,
                        int height,
                        SDL_RendererFlip flip,
                        double conor)
{
    SDL_Rect anim{animX, animY, animW, animH};
    SDL_Rect pos{x, y, width, height};

    SDL_RenderCopyEx(this->gRenderer, image->mTexture, &anim, &pos, conor, NULL, flip);
}

void Context::DrawImage(Image *image,
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
                        int alpha)
{
    SDL_Rect anim{animX, animY, animW, animH};
    SDL_Rect pos{x, y, width, height};

    SDL_SetTextureAlphaMod(image->mTexture, alpha);
    SDL_RenderCopyEx(this->gRenderer, image->mTexture, &anim, &pos, conor, NULL, flip);
    SDL_SetTextureAlphaMod(image->mTexture, 255);
}

void Context::DrawImage(Image *image,
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
                        int rotY)
{
    SDL_Rect anim{animX, animY, animW, animH};
    SDL_Rect pos{x, y, width, height};
    SDL_Point center{rotX, rotY};

    SDL_SetTextureAlphaMod(image->mTexture, alpha);
    SDL_RenderCopyEx(this->gRenderer, image->mTexture, &anim, &pos, conor, &center, flip);
    SDL_SetTextureAlphaMod(image->mTexture, 255);
}

Context::~Context()
{
    this->Close();
    printf(" here ");
}

Context ctx(800, 600);
SDL_Renderer *Image::gRenderer = ctx.getRenderer();
