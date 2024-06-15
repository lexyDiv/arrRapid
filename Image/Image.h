#pragma once

#include "../rapid.h"

class Image
{
public:
	SDL_Texture *mTexture;
	static SDL_Renderer *gRenderer;
	// Initializes variables
	Image(std::string path);
	Image(int width, int height);

	// Deallocates memory
	~Image();

	// Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer *gRenderer);

	// Deallocates texture
	void free();

	// Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Set blending
	void setBlendMode(SDL_BlendMode blending);

	// Set alpha modulation
	void setAlpha(Uint8 alpha);

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture

	// Image dimensions
	int mWidth;
	int mHeight;
};