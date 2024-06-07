#include <iostream>
#include <SDL2/SDL.h>

constexpr int SCREEN_WIDTH {800};
constexpr int SCREEN_HEIGHT { 600 };

using namespace std;

int main(int argc, char* args[])
{   
 SDL_Window* window{nullptr};
 SDL_Surface* screenShurface{nullptr};

 if (SDL_Init(SDL_INIT_VIDEO) < 0)
 {
 // printf("PIZDA", SDL_GetError());
 }
 else
 {
  window = SDL_CreateWindow(
  "SDL TRY",
   SDL_WINDOWPOS_CENTERED_MASK,
   SDL_WINDOWPOS_CENTERED_MASK,
   SCREEN_WIDTH,
   SCREEN_HEIGHT,
   SDL_WINDOW_SHOWN
  );

  if (window == nullptr)
  {
  // printf("pizda 2", SDL_GetError());
  }
  else
  {
   screenShurface = SDL_GetWindowSurface(window);

   SDL_Rect q{10, 10, 100, 100};

   SDL_FillRect(
    screenShurface,
    &q,
    SDL_MapRGB(screenShurface->format, 255, 255, 255)
   );
   SDL_UpdateWindowSurface(window);
   SDL_Delay(2000);
  }
  SDL_DestroyWindow(window);
  SDL_Quit();

 }

 return 0;
}
