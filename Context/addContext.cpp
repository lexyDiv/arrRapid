#include "Context.cpp"

Context ctx(800, 600);
SDL_Renderer *Image::gRenderer = ctx.getRenderer();
Image *image = new Image("src/zombi.png");
