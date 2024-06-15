#include "function.cpp"



int main(int argc, char *args[])
{



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
		SDL_LockTexture(miniMap->mTexture, &rect, &mRawPixels2, &mRawPitch2);
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

		SDL_UnlockTexture(miniMap->mTexture);
		mRawPixels2 = NULL;
		mRawPitch2 = 0;

		// gStreamingTexture.render(
		// 	0,
		// 	0);
		ctx.DrawImage(miniMap, 0, 0, 64, 64, 600, 30, 200, 200);

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