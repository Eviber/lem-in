/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/03 16:32:21 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static void		get_texture(SDL_Renderer *render, SDL_Texture **texture)
{
	SDL_Surface		*surface;

	surface = SDL_LoadBMP("src/visu/dirt.bmp");
	*texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
}

static void		anthill_gen(/*SDL_Window *win, */SDL_Renderer *render, t_env *env)
{
	SDL_Texture		*bg;
	SDL_Rect		bg_pos;

	if (!env)
		return ;
	bg_pos.x = 0;
	bg_pos.y = 0;
	bg_pos.w = WIN_W;
	bg_pos.h = WIN_H;
	get_texture(render, &bg);
	while (!SDL_QuitRequested())
	{
		SDL_RenderClear(render);
		SDL_RenderCopy(render, bg, NULL, &bg_pos);
		SDL_RenderPresent(render);
	}
	SDL_DestroyTexture(bg);
}

int				lem_in_visu(t_env *env)
{
	SDL_Window		*win;
	SDL_Renderer	*render;

	SDL_Init(SDL_INIT_VIDEO);
	if ((win = SDL_CreateWindow("Lem-in", 0, 0, WIN_W, WIN_H, 0)) && \
	(render = SDL_CreateRenderer(win, -1, 0)))
	{
		anthill_gen(/*win, */render, env);
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (0);
	}
	return (1);
}
