#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include "rapid.h"
#include "Units/testUnit/Unit.h"
// #include <ffmpeg/swscale.h>
//  Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
// 1536 256
// Texture wrapper class
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
    bool loadFromFile(std::string path);

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
        int gabY);

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

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Scene sprites
SDL_Rect gSpriteClips[4];
// LTexture gSpriteSheetTexture;
LTexture *gSpriteSheetTexture = new LTexture();

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
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
    // Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(
    int x,
    int y,
    int conor,
    int alpha,
    int animX,
    int animY,
    int animStepX,
    int animStepY,
    int gabX,
    int gabY)
{
    // Set rendering space and render to screen
    // SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    //  int hz = this->anim.x; // ok
    //  Set clip rendering dimensions
    //  if (clip != NULL)
    //  {
    //      renderQuad.w = clip->w;
    //      renderQuad.h = clip->h;
    //  }

    // Render to screen
    // SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
     


    SDL_Rect srcrect = {animX, animY, animStepX, animStepY}; // anim
    SDL_Rect dstrect = {x, y, gabX, gabY};// pos
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    // SDL_SetTextureColorMod( mTexture,10,10,255);
    SDL_SetTextureAlphaMod(mTexture, alpha);
    SDL_RenderCopyEx(gRenderer, mTexture, &srcrect, &dstrect, conor, NULL, flip);
    
    //   //  this->conor += 1;
    //     if (this->conor >= 360)
    //     {
    //         this->conor = 0;
    //     }

    //     if (this->a == 255 || this->a == 0)
    //     {
    //         this->aV = -this->aV;
    //     }
    //     if (this->tik % 6 == 0)
    //     {
    //         this->animX += this->animStep;
    //         if (this->animX == 1536)
    //         {
    //             this->animX = 0;
    //         }
    //     }
    //     this->anim = {this->animX, 0, this->animStep, 256};
    //     this->tik++;
    //     if (this->tik == 10000)
    //     {
    //         this->tik = 0;
    //     }
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
{
    // Initialization flag
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

        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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

    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    // Load sprite sheet texture
    if (!gSpriteSheetTexture->loadFromFile("src/zombi.png"))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
    }
    else
    {

        // Set top left sprite
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 1536 / 6;
        gSpriteClips[0].h = 256;

        // Set top right sprite
        //  gSpriteClips[ 1 ].x = 100;
        //  gSpriteClips[ 1 ].y =   0;
        //  gSpriteClips[ 1 ].w = 100;
        //  gSpriteClips[ 1 ].h = 100;

        // //Set bottom left sprite
        // gSpriteClips[ 2 ].x =   0;
        // gSpriteClips[ 2 ].y = 100;
        // gSpriteClips[ 2 ].w = 100;
        // gSpriteClips[ 2 ].h = 100;

        // //Set bottom right sprite
        // gSpriteClips[ 3 ].x = 100;
        // gSpriteClips[ 3 ].y = 100;
        // gSpriteClips[ 3 ].w = 100;
        // gSpriteClips[ 3 ].h = 100;
    }

    return success;
}

void close()
{
    // Free loaded images
    gSpriteSheetTexture->free();
    delete gSpriteSheetTexture;
    gSpriteSheetTexture = nullptr;
    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{

    rapid<Unit<LTexture *> *> *arr = new rapid<Unit<LTexture *> *>;

    arr->backForce(2);

    arr->push(new Unit<LTexture *>(0, 0, 0, 255, 200, 299, gSpriteSheetTexture));
    arr->push(new Unit<LTexture *>(300, 0, 0, 255, 200, 299, gSpriteSheetTexture));
    arr->norm();

    // Start up SDL and create window
    int tik = 0;
    int animX = 0;

    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // While application is running
            int num = 0;
            while (!quit)
            {
                // num++;
                // if(num == 100)
                // {
                //     gSpriteSheetTexture.free();
                // }
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render top left sprite
                // gSpriteSheetTexture->render(0, 0, &gSpriteClips[0]); //// !!!!!
                arr->forEach([](Unit<LTexture*>el){el->draw()});

                // Update screen
                SDL_RenderPresent(gRenderer);

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}

// int SDL_RenderCopyEx(SDL_Renderer*          renderer,
//                  SDL_Texture*           texture,
//                  const SDL_Rect*        srcrect,
//                  const SDL_Rect*        dstrect,
//                  const double           angle,
//                  const SDL_Point*       center,
//                  const SDL_RendererFlip flip);