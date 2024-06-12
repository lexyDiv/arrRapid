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
        this->gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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
                SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
    };
}

void Context::Close()
{
    SDL_DestroyRenderer(this->gRenderer);
    SDL_DestroyWindow(this->gWindow);
    this->gWindow = NULL;
    this->gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
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

Context::~Context()
{
    this->Close();
}
