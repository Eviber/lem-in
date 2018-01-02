#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int		main(void)
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	SDL_Surface		*surf;
	SDL_Rect		rect;
	SDL_Texture		*textur;
	int				rgb[3] = {0};

	rgb[0] = 255;
	rgb[1] = 255;
	rgb[2] = 255;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 960;
	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("Test", 0, 0, 1280, 960, 0);
	rend = SDL_CreateRenderer(win, -1, 0);
	SDL_SetRenderDrawColor(rend, rgb[0], rgb[1], rgb[2], 255);
	surf = SDL_LoadBMP("dirt.bmp");
	textur = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	while (!SDL_QuitRequested())
	{
		SDL_RenderClear(rend);
		SDL_RenderCopy(rend, textur, NULL, &rect);
/*		if (rgb[0] < 255 && rgb[1] == 0)
			rgb[0]++;
		else if (rgb[1] < 255 && rgb[0] == 255 && rgb[2] == 0)
			rgb[1]++;
		else if (rgb[2] < 255 && rgb[0] == 255 && rgb[1] == 255)
			rgb[2]++;
		else
			rgb[0] = rgb[1] = rgb[2] = rgb[0] - 1;*/
		thickLineRGBA(rend, 50, 50, 150, 180, 5, 0, 0, 0, 150);
		filledCircleRGBA(rend, 50, 50, 51, 96, 96, 96, 255);
		aacircleRGBA(rend, 50, 50, 50, 0, 0, 0, 255);
		aacircleRGBA(rend, 50, 50, 51, 0, 0, 0, 255);
		filledCircleRGBA(rend, 150, 180, 25, 96, 96, 96, 255);
		aacircleRGBA(rend, 150, 180, 25, 0, 0, 0, 255);
		aacircleRGBA(rend, 150, 180, 26, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	}
	SDL_Quit();
	return (0);
}
