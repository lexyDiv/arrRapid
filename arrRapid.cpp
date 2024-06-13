/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, standard IO, math, and strings
#include <thread>
#include <chrono>

// #include "Context/addContext.cpp"
#include "Cell/Cell.cpp"



int main(int argc, char *args[])
{

	arr->backForce(300);
	for (int i = 0; i < 300; i++)
	{
		arr->push(new rapid<Cell *>);
		arr->getItem(i)->backForce(200);
		for (int k = 0; k < 200; k++)
		{
			Cell *cell = new Cell(k + 600, i, 2);
			arr->getItem(i)->push(cell);
		}
		arr->getItem(i)->norm();
	}
	arr->norm();

	int ver = 0;

	bool quit = false;
	SDL_Event e;
	double conor = 0;
	int x = 200;
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

		// ctx.ClearRect(0, 0, 800, 600);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.h = 600;
		rect.w = 600;
		SDL_RenderSetClipRect(ctx.getRenderer(),
							  &rect);
		ctx.FillRect(0, 0, 600, 600, "white");

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 100, 100, 300, 300);
		ctx.DrawImage(test, 0, 0, 200, 300, 0, 0, 200, 300);

		SDL_Rect rect2;
		rect2.x = 600;
		rect2.y = 300;
		rect2.w = 200;
		rect2.h = 600;
		SDL_RenderSetClipRect(ctx.getRenderer(),
							  &rect2);
		ctx.FillRect(600, 300, 200, 600, "blue");
		///////////////////////////////////////////
		SDL_Rect rect3;
		rect3.x = 600;
		rect3.y = 0;
		rect3.w = 200;
		rect3.h = 300;
		SDL_RenderSetClipRect(ctx.getRenderer(),
							  &rect3);
		//ctx.FillRect(600, 0, 200, 300, "green", 50);
		if (x == 200)
		{
			arr->forEach([ver](rapid<Cell *> *line)
						 { line->forEach([ver](Cell *cell, int index)
										 { cell->draw(index, ver); }); });
		}
		else
		{
		
			arr->getItem(ver)->forEach([ver](Cell *cell, int index)
									   { cell->draw(index, ver); });
		}

		ver++;
		if (ver == 300)
		{
			ver = 0;
		}
		// if (x % 100 == 0)
		// {
		// 	ctx.FillRect(600, 0, 200, 300, "red");
		// 	ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 600, 50, 200, 200);
		// }

		ctx.End();
		conor += 1;
		x++;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	ctx.Close();
	delete image;
	image = nullptr;
	delete test;
	test = nullptr;
	return 0;
}