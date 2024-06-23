#include "function.cpp"


//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;



bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load prompt texture
	// if( !gPromptTexture.loadFromFile( "src/sound/prompt.png" ) )
	// {
	// 	printf( "Failed to load prompt texture!\n" );
	// 	success = false;
	// }

	//Load music
	gMusic = Mix_LoadMUS( "src/sound/beat.wav" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	//Load sound effects
	gScratch = Mix_LoadWAV( "src/sound/scratch.wav" );
	if( gScratch == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	gHigh = Mix_LoadWAV( "src/sound/high.wav" );
	if( gHigh == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMedium = Mix_LoadWAV( "src/sound/medium.wav" );
	if( gMedium == NULL )
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gLow = Mix_LoadWAV( "src/sound/low.wav" );
	if( gLow == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	return success;
}




int main(int argc, char *args[])
{
	loadMedia();

	std::srand(time(NULL));
	ctx.getFont();
	getField();

	int ver = 0;

	bool quit = false;
	SDL_Event e;

	
	int ticker = 0;
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
			if (e.type == SDL_KEYDOWN)
			{
				// console.log(to_string(e.type));
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				mouse.move(e.motion.x, e.motion.y);
				// console.log(to_string(e.motion.x));
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				// console.log(to_string(e.button.button)); // 1, 2, 3
				mouse.pressKey(e.button.button);
			}
			if (e.type == SDL_MOUSEBUTTONUP)
			{
				// console.log(to_string(e.button.button)); // 1, 2, 3
				mouse.upKey(e.button.button);
			}
			if (e.type == SDL_MOUSEWHEEL)
			{
			
			  console.whellOrder(e.motion.yrel);
			}
		}
		console.proc(mouse.x, mouse.y, mouse.leftKey);


if(ticker == 100)
{
	Mix_PlayChannel( -1, gHigh, 0 );
	console.log("try sound paly");
}


		ctx.ClearRect(0, 0, 800, 600);

		ctx.CreateDrawZone(0, 0, 600, 600);
		ctx.FillRect(0, 0, 600, 600, "yellow");

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 100, 100, 300, 300);

		ctx.CreateDrawZone(600, 0, 200, 600);
		int index = ver * 64;
		int hor = 0;
		ctx.PixelHendler(miniMap, 0, ver, 64, 1, [ver](Uint32 *pixelsArr, SDL_PixelFormat *pixelFormat)
						 { arr->getItem(ver)->forEach([pixelsArr, pixelFormat](Cell *cell, int index)
													  {
														  pixelsArr;
														  pixelFormat;
														  Color color = cell->color;
														  Uint8 r = color.R;
														  Uint8 g = color.G;
														  Uint8 b = color.B;
														  Uint8 a = cell->A;
														  Uint32 hzRes = SDL_MapRGBA(pixelFormat, r, g, b, a);
														  pixelsArr[index] = hzRes; }); }

		);
		ver++;
		if (ver == 64)
		{
			ver = 0;
		}
		ctx.FillRect(600, 0, 200, 600, "white", 255);
		ctx.FillRect(600, 0, 200, 600, "blue", 100);
		ctx.DrawImage(miniMap, 0, 0, 64, 64, 600, 30, 200, 200);

		console.draw();
		ctx.End();

		ticker++;

	}
	ctx.Close();

	delete image;
	image = nullptr;


	arr->forEach([](rapid<Cell *> *line)
				 {
		line->forEach([](Cell* cell){
			delete cell;
			cell = nullptr;
		});
		delete line;
		line = nullptr; });
	delete arr;
	arr = nullptr;
	// delete test;
	// test = nullptr;


	//Free the sound effects
	Mix_FreeChunk( gScratch );
	Mix_FreeChunk( gHigh );
	Mix_FreeChunk( gMedium );
	Mix_FreeChunk( gLow );
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;
	
	//Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;


	return 0;
}