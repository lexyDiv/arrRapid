#include "function.cpp"

int main(int argc, char *args[])
{

	getField();

	int ver = 0;

	bool quit = false;
	SDL_Event e;
	double conor = 0;
    float x = 200;
	int ax = 0;
    Point arrPoints[]{{300, 300}, {400, 400}};
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


		ctx.CreateDrawZone(0, 0, 600, 600);
		ctx.FillRect(0, 0, 600, 600, "yellow");

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, x, 100, 300, 300);

		

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
		
		ctx.DrawImage(miniMap, 0, 0, 64, 64, 600, 30, 200, 200);

		ctx.End();

		x+= 2;
		x == 800 ? x = 0 : x = x;
		//std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	ctx.Close();

	delete image;
	image = nullptr;
	// delete test;
	// test = nullptr;
	return 0;
}