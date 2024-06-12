/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, standard IO, math, and strings
#include <thread>
#include <chrono>
// #include "Context/Context.cpp"
#include "Context/addContext.cpp"

int main(int argc, char *args[])
{

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

		ctx.ClearRect(0, 0, 800, 600);

		ctx.FillRect(30, 0, 50, 50, "green");
		ctx.FillRect(100, 0, 50, 50, "red");
		ctx.FillRect(150, 0, 50, 50, "blue", 150);
		ctx.FillRect(250, 200, 50, 50);
		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 0, 0, 100, 100, SDL_FLIP_NONE, 0, 255, 50, 50, 255, 255, 0);
		ctx.FillRect(30, 70, 50, 50, 0, 0, 0, 100);

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 300, 300, 150, 150);
		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, x, 300, 100, 100, SDL_FLIP_NONE, conor, 200, 50, 50, 255, 255, 255);

		ctx.End();
		conor += 1;
		x++;
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
	ctx.Close();
	delete image;
	image = nullptr;
	return 0;
}