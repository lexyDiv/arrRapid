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

struct Obj 
{
    int x, y;
    int w, h;
};

Obj obj{10, 10, 100, 100};

    SDL_BlitSurface(loh, nullptr, gShurface, nullptr);
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(2000);
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
    SDL_DestroyWindow(gWindow);
}

