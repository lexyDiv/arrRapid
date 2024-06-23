#include "function.cpp"

int main(int argc, char *args[])
{

	std::srand(time(NULL));
	ctx.getFont();
	getField();

	int ver = 0;

	bool quit = false;
	SDL_Event e;

	Point *arrPoints = new Point[]{{100, 100}, {100, 200}, {200, 200}, {200, 100}};

	
    for(int i = 0; i < 1; i++)
	{
		console.log("Papa mega super loh!!! This is true.");
	}


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
		 if(ticker % 40 == 0)
		 {
			console.log(to_string(ticker));
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
		if (ticker == 1000)
		{
			ticker = 0;
			// console.clear();
		}
	}
	ctx.Close();

	delete image;
	image = nullptr;
	delete arrPoints;
	arrPoints = nullptr;

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
	return 0;
}