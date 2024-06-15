#include "function.cpp"

class LTexture
{
public:
	SDL_Texture *mTexture;

	// Surface pixels
	SDL_Surface *mSurfacePixels;
	// Initializes variables
	double colorCode = 4294967295;
	LTexture();

	// Deallocates memory
	~LTexture();

	// Loads image at specified path

	// Loads image into pixel buffer

	// Creates image from preloaded pixels



	// Creates blank texture
	bool createBlank(int width, int height);

	// Deallocates texture
	void free();

	// Set color modulation
	

	// Set blending
	

	// Set alpha modulation
	

	// Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// Gets image dimensions

	// Pixel accessors

	

private:
	// The actual hardware texture

	// Raw pixels
	void *mRawPixels;
	int mRawPitch;

	// Image dimensions
	int mWidth;
	int mHeight;
};

// A test animation stream
class DataStream
{
public:
	// Initializes internals
	DataStream();

	// Loads initial data
	bool loadMediaData();

	// Deallocator
	void free();

	// Gets current frame data

private:
	// Internal data
	SDL_Surface *mImages[4];
	int mCurrentImage;
	int mDelayFrames;
};

// Starts up SDL and creates window


// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Scene textures
LTexture gStreamingTexture;

// Animation stream
DataStream gDataStream;

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;

	mSurfacePixels = NULL;
	mRawPixels = NULL;
	mRawPitch = 0;
}

LTexture::~LTexture()
{
	// Deallocate
	free();
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	// Get rid of preexisting texture
	free();

	// Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(ctx.getRenderer(), textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	// Return success
	return mTexture != NULL;
}
#endif

bool LTexture::createBlank(int width, int height)
{
	// Get rid of preexisting texture
	// free();

	// Create uninitialized texture
	mTexture = SDL_CreateTexture(ctx.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (mTexture == NULL)
	{
		printf("Unable to create streamable blank texture! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		mWidth = width;
		mHeight = height;
	}

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

	// Free surface if it exists
	if (mSurfacePixels != NULL)
	{
		SDL_FreeSurface(mSurfacePixels);
		mSurfacePixels = NULL;
	}
}







void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = {600, 30, 200, 200};

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopyEx(ctx.getRenderer(), mTexture, clip, &renderQuad, angle, center, flip);
}



// 0xFF0000FF red
// 0x0000FFFF blue

DataStream::DataStream()
{
	mImages[0] = NULL;
	mImages[1] = NULL;
	mImages[2] = NULL;
	mImages[3] = NULL;

	mCurrentImage = 0;
	mDelayFrames = 4;
}

bool DataStream::loadMediaData()
{
	bool success = true;

	// for (int i = 0; i < 4; ++i)
	///{
	std::stringstream path;
	path << "src/map" << ".png";

	SDL_Surface *loadedSurface = IMG_Load(path.str().c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load %s! SDL_image error 2: %s\n", path.str().c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		mImages[0] = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
	}

	SDL_FreeSurface(loadedSurface);
	//}

	return success;
}

void DataStream::free()
{
	for (int i = 0; i < 4; ++i)
	{
		SDL_FreeSurface(mImages[i]);
		mImages[i] = NULL;
	}
}



// bool init()
// {
// 	//Initialization flag
// 	bool success = true;

// 	//Initialize SDL
// 	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
// 	{
// 		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
// 		success = false;
// 	}
// 	else
// 	{
// 		//Set texture filtering to linear
// 		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
// 		{
// 			printf( "Warning: Linear texture filtering not enabled!" );
// 		}

// 		//Seed random
// 		srand( SDL_GetTicks() );

// 		//Create window
// 		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
// 		if( gWindow == NULL )
// 		{
// 			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
// 			success = false;
// 		}
// 		else
// 		{
// 			//Create renderer for window
// 			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
// 			if( gRenderer == NULL )
// 			{
// 				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
// 				success = false;
// 			}
// 			else
// 			{
// 				//Initialize renderer color
// 				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

// 				//Initialize PNG loading
// 				int imgFlags = IMG_INIT_PNG;
// 				if( !( IMG_Init( imgFlags ) & imgFlags ) )
// 				{
// 					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
// 					success = false;
// 				}
// 			}
// 		}
// 	}

// 	return success;
// }

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load blank texture
	if (!gStreamingTexture.createBlank(64, 64))
	{
		printf("Failed to create streaming texture!\n");
		success = false;
	}

	// Load data stream
	// if (!gDataStream.loadMediaData())
	// {
	// 	printf("Unable to load data stream!\n");
	// 	success = false;
	// }

	return success;
}

void close()
{
	// Free loaded images
	gStreamingTexture.free();
	gDataStream.free();

	// Destroy window
	//  SDL_DestroyRenderer( gRenderer );
	//  SDL_DestroyWindow( gWindow );
	//  gWindow = NULL;
	//  gRenderer = NULL;

	// //Quit SDL subsystems
	// IMG_Quit();
	// SDL_Quit();
}

int main(int argc, char *args[])
{

	if (!loadMedia())
	{
		printf("Failed to load media!\n");
	}

	getField();

	int ver = 0;

	bool quit = false;
	SDL_Event e;
	double conor = 0;
	int x = 200;
	auto pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	while (!quit)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		ctx.ClearRect(0, 0, 800, 600);

		////////////////////////////////////////////////////// injeckt

		// gStreamingTexture.lockTexture();
		// gStreamingTexture.copyRawPixels32(gDataStream.getBuffer());
		// gStreamingTexture.unlockTexture();

		// Render frame

		//////////////////////////////////////////////////////
		//  ctx.FillRect(0, 0, 150, 150, "red");
		SDL_Rect rect2;
		rect2.x = 0;
		rect2.y = 0;
		rect2.h = 600;
		rect2.w = 600;
		SDL_RenderSetClipRect(ctx.getRenderer(),
							  &rect2);
		ctx.FillRect(0, 0, 600, 600, "white");

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, x, 100, 300, 300);

		// ctx.DrawImage(test, 0, 0, 200, 300, 0, 0, 200, 300);

		SDL_Rect rect5;
		rect5.x = 600;
		rect5.y = 300;
		rect5.w = 200;
		rect5.h = 600;
		SDL_RenderSetClipRect(ctx.getRenderer(),
							  &rect5);
		ctx.FillRect(600, 300, 200, 600, "black");
		// ///////////////////////////////////////////
		SDL_Rect rect3;
		rect3.x = 600;
		rect3.y = 0;
		rect3.w = 200;
		rect3.h = 300;
		SDL_RenderSetClipRect(ctx.getRenderer(),
							  &rect3);
		// ctx.FillRect(600, 0, 200, 300, "green", 50);

		SDL_Rect rect{0, 0, 64, 64};
		void *mRawPixels2;
		int mRawPitch2;
		SDL_LockTexture(gStreamingTexture.mTexture, &rect, &mRawPixels2, &mRawPitch2);
		Uint32 *pixelsArr = (Uint32 *)mRawPixels2;

		// i = 0; i < 64 * 205;
		int index = ver * 64;
		int hor = 0;
		for (int i = index; i < index + 64; i++)
		{
			Color color = arr->getItem(ver)->getItem(hor)->color;
			hor++;
			Uint8 r = color.R;
			Uint8 g = color.G;
			Uint8 b = color.B;
			Uint8 a = 255;

			Uint32 hzRes = SDL_MapRGBA(pixelFormat, r, g, b, a);

			pixelsArr[i] = hzRes;
		}

		ver++;
		if (ver == 64)
		{
			ver = 0;
		}

		SDL_UnlockTexture(gStreamingTexture.mTexture);
		mRawPixels2 = NULL;
		mRawPitch2 = 0;

		gStreamingTexture.render(
			0,
			0);

		ctx.End();
		x++;
		x == 800 ? x = 0 : x = x;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	ctx.Close();

	delete image;
	image = nullptr;
	// delete test;
	// test = nullptr;
	return 0;
}