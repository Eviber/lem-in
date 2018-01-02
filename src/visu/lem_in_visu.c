/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/02 18:56:50 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "lem-in.h"
#include "parser_lem-in.h"

static void			get_texture(SDL_Renderer *render, SDL_Texture **texture)
{
	SDL_Surface		*surface;

	surface = SDL_LoadBMP("src/visu/dirt.bmp");
	*texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}

int					lem_in_visu(t_env *env)
{
	SDL_Window		*win;
	SDL_Texture		*bg;
	SDL_Renderer	*render;
	SDL_Rect		new;

	new.x = 0;
	new.y = 0;
	new.w = 1280;
	new.h = 960;
	if (!env)
		return (1);
	SDL_Init(SDL_INIT_VIDEO);
	if ((win = SDL_CreateWindow("Lem-in", 0, 0, 1280, 960, 0)) && \
	(render = SDL_CreateRenderer(win, -1, 0)))
	{
		get_texture(render, &bg);
		while (!SDL_QuitRequested())
		{
			SDL_RenderClear(render);
			SDL_RenderCopy(render, bg, NULL, &new);
			SDL_RenderPresent(render);
		}
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (0);
	}
	return (1);
}
