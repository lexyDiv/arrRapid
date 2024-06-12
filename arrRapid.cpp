/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, standard IO, math, and strings
#include <thread>
#include <chrono>
//#include "Context/Context.cpp"
#include "Context/addContext.cpp"



//Context ctx(800, 600);

Image *image = new Image("src/zombi.png", ctx.getRenderer());

int main(int argc, char *args[])
{

	bool quit = false;
	SDL_Event e;
	double conor = 0;
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

		
		 ctx.ClearRect(0, 0, 400, 600);
		
		SDL_SetRenderDrawColor(ctx.getRenderer(), 0, 0, 0, 0);
		SDL_Rect rect1 = {10, 10, 50, 50};
		SDL_RenderFillRect(ctx.getRenderer(), &rect1);

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 0, 0, 100, 100, SDL_FLIP_NONE, 0, 255, 50, 50, 255, 255, 0);
		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 200, 200, 100, 100, SDL_FLIP_NONE, conor, 100, 50, 50, 255, 255, 255);

		ctx.DrawImage(image, 0, 0, 1536 / 6, 256, 300, 300, 150, 150);

		ctx.End();
		conor += 1;
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	ctx.Close();
	delete image;
	image = nullptr;
	return 0;
}