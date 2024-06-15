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
	bool loadFromFile(std::string path);

	// Loads image into pixel buffer
	bool loadPixelsFromFile(std::string path);

	// Creates image from preloaded pixels
	bool loadFromPixels();

#if defined(SDL_TTF_MAJOR_VERSION)
	// Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	// Creates blank texture
	bool createBlank(int width, int height);

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

	// Pixel accessors
	Uint32 *getPixels32();
	Uint32 getPixel32(Uint32 x, Uint32 y);
	Uint32 getPitch32();
	Uint32 mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void copyRawPixels32(void *pixels);
	bool lockTexture();
	bool unlockTexture();

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
	void *getBuffer();

private:
	// Internal data
	SDL_Surface *mImages[4];
	int mCurrentImage;
	int mDelayFrames;
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

bool LTexture::loadFromFile(std::string path)
{
	// Load pixels
	if (!loadPixelsFromFile(path))
	{
		printf("Failed to load pixels for %s!\n", path.c_str());
	}
	else
	{
		// Load texture from pixels
		if (!loadFromPixels())
		{
			printf("Failed to texture from pixels from %s!\n", path.c_str());
		}
	}

	// Return success
	return mTexture != NULL;
}

bool LTexture::loadPixelsFromFile(std::string path)
{
	// Free preexisting assets
	free();

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error 1: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Convert surface to display format
		mSurfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(ctx.gWindow), 0);
		if (mSurfacePixels == NULL)
		{
			printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = mSurfacePixels->w;
			mHeight = mSurfacePixels->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return mSurfacePixels != NULL;
}

bool LTexture::loadFromPixels()
{
	// Only load if pixels exist
	if (mSurfacePixels == NULL)
	{
		printf("No pixels loaded!");
	}
	else
	{
		// Color key image
		SDL_SetColorKey(mSurfacePixels, SDL_TRUE, SDL_MapRGB(mSurfacePixels->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(ctx.getRenderer(), mSurfacePixels);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from loaded pixels! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			// Get image dimensions
			mWidth = mSurfacePixels->w;
			mHeight = mSurfacePixels->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(mSurfacePixels);
		mSurfacePixels = NULL;
	}

	// Return success
	return mTexture != NULL;
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
	free();

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

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	// Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
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

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Uint32 *LTexture::getPixels32()
{
	Uint32 *pixels = NULL;

	if (mSurfacePixels != NULL)
	{
		pixels = static_cast<Uint32 *>(mSurfacePixels->pixels);
	}

	return pixels;
}

Uint32 LTexture::getPixel32(Uint32 x, Uint32 y)
{
	// Convert the pixels to 32 bit
	Uint32 *pixels = static_cast<Uint32 *>(mSurfacePixels->pixels);

	// Get the pixel requested
	return pixels[(y * getPitch32()) + x];
}

Uint32 LTexture::getPitch32()
{
	Uint32 pitch = 0;

	if (mSurfacePixels != NULL)
	{
		pitch = mSurfacePixels->pitch / 4;
	}

	return pitch;
}

Uint32 LTexture::mapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	Uint32 pixel = 0;

	if (mSurfacePixels != NULL)
	{
		pixel = SDL_MapRGBA(mSurfacePixels->format, r, g, b, a);
	}

	return pixel;
}

bool LTexture::lockTexture()
{
	bool success = true;

	// Texture is already locked
	SDL_Rect rect{0, 0, 64, 64};

	if (SDL_LockTexture(mTexture, &rect, &mRawPixels, &mRawPitch) != 0)
	{
		printf("Unable to lock texture! %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

bool LTexture::unlockTexture()
{
	bool success = true;

	// Texture is not locked
	if (mRawPixels == NULL)
	{
		printf("Texture is not locked!\n");
		success = false;
	}
	// Unlock texture
	else
	{
		SDL_UnlockTexture(mTexture);
		mRawPixels = NULL;
		mRawPitch = 0;
	}

	return success;
}

void LTexture::copyRawPixels32(void *pixels)
{

	//   char str1[] = "Пример строки";
	//   char str2[40];
	//   char str3[60];

	//   memcpy (str2, str1, strlen(str1)+1);               // копируем строку str1  и сохраняем в str2
	//   memcpy (str3, "Копирование успешно выполнено",60); // копируем 60 байт строки и сохраняем в str3

	// Texture is locked
	if (mRawPixels != NULL)
	{
		// Copy to locked pixels

		// pixels
		Uint32 *pixelsArr = (Uint32 *)pixels;
		// Uint32* colorkey = SDL_MapRGB( gStreamingTexture.mSurfacePixels, 0, 0xFF, 0xFF );
		// pixelsArr[0];
		// std::string mess = std::to_string(pixelsArr[0]) + " res :";
		Uint8 r = 0;
		Uint8 g = 128;
		Uint8 b = 0;
		Uint8 a = 255;

		auto pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

		Uint32 hzRes = SDL_MapRGBA(pixelFormat, r, g, b, a);

		for (int i = 0; i < 64 * 64; i++)
		{
			pixelsArr[i] = hzRes;
		}
		// printf(mess.c_str());
		memcpy(mRawPixels, pixels, mRawPitch * mHeight);
		// std::string ggg = std::to_string(mRawPitch) + " ";
		// printf(ggg.c_str()); 256
	}
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

void *DataStream::getBuffer()
{
	--mDelayFrames;
	if (mDelayFrames == 0)
	{
		++mCurrentImage;
		mDelayFrames = 4;
	}

	if (mCurrentImage == 4)
	{
		mCurrentImage = 0;
	}

	return mImages[mCurrentImage]->pixels;
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
	if (!gDataStream.loadMediaData())
	{
		printf("Unable to load data stream!\n");
		success = false;
	}

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
		gStreamingTexture.render(
			(ctx.SCREEN_WIDTH - gStreamingTexture.getWidth()) / 2,
			(ctx.SCREEN_HEIGHT - gStreamingTexture.getHeight()) / 2);

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

		ctx.End();
		x++;
		x == 800 ? x = 0 : x = x;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	ctx.Close();

	// delete image;
	// image = nullptr;
	// delete test;
	// test = nullptr;
	return 0;
}