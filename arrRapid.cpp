#include <iostream>
#include <SDL2/SDL.h>

constexpr int SCREEN_WIDTH{800};
constexpr int SCREEN_HEIGHT{600};

using namespace std;

static SDL_Window *gWindow{nullptr};
static SDL_Surface *gShurface{nullptr};
static SDL_Surface *loh{nullptr};

bool Init();
bool LoadMedia();
void Close();

int main(int argc, char *args[])
{
    if(!Init() || !LoadMedia())
    {
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    

struct Obj 
{
    int x, y;
    int w, h;
};

SDL_Rect q{0, 0, 1200, 675}; // anmX, animY
SDL_Rect q2{0, 0, 200, 300};  // x, y

    SDL_BlitSurface(loh, &q, gShurface, &q2);
    SDL_UpdateWindowSurface(gWindow);

    }

    Close();
    return 0;
}

bool Init()
{
    bool saccess = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << " bad " << endl;
        saccess = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(
            "image",
            0,
            0,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_OPENGL
        );
        if(gWindow == nullptr)
        {
            saccess = false;
        }
        else
        {
            gShurface = SDL_GetWindowSurface(gWindow);
        }
        return saccess;
    }
    return 0;
}

bool LoadMedia()
{
    loh = SDL_LoadBMP("src/loh.bmp");
    if(loh == nullptr)
    {
        printf("pizda");
        return false;
    }
    return true;
}

void Close()
{
    SDL_FreeSurface(loh);
    loh = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    SDL_Quit();
}

