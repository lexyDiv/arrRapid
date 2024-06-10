#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "../rapid.h"

class LTexture
{
public:
    int animStep = 1536 / 6;
    int animX = 0;
    int tik = 0;
    int a = 0;
    int aV = 1;
    double conor = 0;
    SDL_Rect pos = {200, 100, 250, 250};
    SDL_Rect anim = {this->animX, 0, this->animStep, 256};
    // Initializes variables
    LTexture();

    // Deallocates memory
    ~LTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

    // Deallocates texture
    void free();

    // Renders texture at given point
    void render(
        int x,
        int y,
        int conor,
        int alpha,
        int animX,
        int animY,
        int animStepX,
        int animStepY,
        int gabX,
        int gabY, SDL_Renderer *gRenderer);

    // Gets image dimensions
    int getWidth();
    int getHeight();

private:
    // The actual hardware texture
    SDL_Texture *mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *gRenderer)
{
    // Get rid of preexisting texture
    free();

    // The final texture
    SDL_Texture *newTexture = NULL;

    // Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color key image
        SDL_Rect rect;
   rect.x = 0;
   rect.y = 0;
   rect.h = 600;
   rect.w = 300;
// SDL_SetClipRect(loadedSurface,
//                                  &rect);


        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        
        // Create texture from surface pixels
       
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        
        SDL_FreeSurface(loadedSurface);
        
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y, int conor, int alpha, int animX, int animY, int animStepX, int animStepY, int gabX, int gabY, SDL_Renderer *gRenderer)
{

    SDL_Rect srcrect = {animX, animY, animStepX, animStepY}; // anim
    SDL_Rect dstrect = {x, y, gabX, gabY};                   // pos
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    // SDL_SetTextureColorMod( mTexture,10,10,255);
    SDL_SetTextureAlphaMod(mTexture, alpha);
    SDL_RenderCopyEx(gRenderer, mTexture, &srcrect, &dstrect, conor, NULL, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}