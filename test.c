#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>

int		main(void)
{
	SDL_Window		*win;
	SDL_Renderer	*rend;
	int				rgb[3] = {0};

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("Test", 0, 0, 640, 480, 0);
	rend = SDL_CreateRenderer(win, -1, 0);
	while (!SDL_QuitRequested())
	{
		if (rgb[0] < 255 && rgb[1] == 0)
			rgb[0]++;
		else if (rgb[1] < 255 && rgb[0] == 255 && rgb[2] == 0)
			rgb[1]++;
		else if (rgb[2] < 255 && rgb[0] == 255 && rgb[1] == 255)
			rgb[2]++;
		else
			rgb[0] = rgb[1] = rgb[2] = rgb[0] - 1;
		SDL_SetRenderDrawColor(rend, rgb[0], rgb[1], rgb[2], 255);
		SDL_RenderClear(rend);
		SDL_RenderPresent(rend);
	}
	SDL_Quit();
	return (0);
}
