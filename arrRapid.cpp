
#include "Units/testUnit/Unit.cpp"
#include "LTexture/LTexture.h"
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init();

bool loadMedia();

void close();

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

// Scene sprites
SDL_Rect gSpriteClips[4];
// LTexture gSpriteSheetTexture;
LTexture *gSpriteSheetTexture = new LTexture();

///////////////////////////////////////  text

/////////////////////////////////////

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

        if (TTF_Init() != 0)
        {
            SDL_Quit();
            return 1;
        }

        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_OPENGL
        );
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
    if (!gSpriteSheetTexture->loadFromFile("src/zombi.png", gRenderer))
    {
        printf("Failed to load sprite sheet texture!\n");
        success = false;
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

    rapid<Unit *> *arr = new rapid<Unit *>;

    arr->backForce(2);

    arr->push(new Unit(0, 0, 0, 255, 200, 200, gSpriteSheetTexture));
    arr->push(new Unit(300, 0, 45, 10, 200, 200, gSpriteSheetTexture));
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
            int tik = 0;
            while (!quit)
            {
                tik++;
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
                // SDL_RenderClear(gRenderer);
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
                
                

                // for(int i = 0; i < 1000; i++)
                // {
                    SDL_Rect rect1 = {0, 0, 300, 600};
                SDL_RenderFillRect(gRenderer, &rect1);

                // SDL_Rect rect2 = {0, 0, 600, 600};
                // SDL_RenderDrawRect(gRenderer, &rect2);
               // }
                // Render top left sprite
                // gSpriteSheetTexture->render(0, 0, &gSpriteClips[0]); //// !!!!!

                SDL_Rect rect;
                rect.x = 0;
                rect.y = 0;
                rect.h = 600;
                rect.w = 300;

                SDL_RenderSetClipRect(gRenderer,
                                      &rect);

                arr->getItem(0)->draw(gRenderer);
                // arr->forEach([](Unit *el)
                //              { el->draw(gRenderer); });
                // SDL_RenderCopy(gRenderer,mTexture,NULL,&abcPosition);
                // SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
                arr->getItem(0)->x += 3;

                rect.x = 0;
                rect.y = 0;
                rect.h = 600;
                rect.w = 800;

                SDL_RenderSetClipRect(gRenderer,
                                      &rect);

                if (tik % 10 == 0)
                {
                    arr->getItem(1)->draw(gRenderer);
                }

                SDL_RenderPresent(gRenderer);

                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            arr->forEach([](Unit *el)
                         {delete el; el = nullptr; });
            delete arr;
            arr = nullptr;
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