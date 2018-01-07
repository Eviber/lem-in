/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/07 16:47:48 by vsporer          ###   ########.fr       */
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

static void		anthill_gen(SDL_Renderer *render, t_visu *venv, t_env *env)
{
	SDL_Texture		*bg;
	SDL_Rect		bg_pos;
	const Uint8		*kb_state;

	if (!env)
		return ;
	bg_pos.x = 0;
	bg_pos.y = -4;
	bg_pos.w = venv->screen.x;
	bg_pos.h = venv->screen.y + 4;
	get_texture(render, &bg);
	get_default_zoom(env->rooms, venv);
	kb_state = SDL_GetKeyboardState(NULL);
	while (!SDL_QuitRequested())
	{
		SDL_RenderClear(render);
		SDL_RenderCopy(render, bg, NULL, &bg_pos);
		get_pipes_visu(render, env->rooms, venv);
		get_rooms_visu(render, env->rooms, venv);
		event_manager(render, kb_state, venv);
		SDL_RenderPresent(render);
	}
	SDL_DestroyTexture(bg);
}

int				lem_in_visu(t_env *env)
{
	t_visu				venv;
	SDL_Window			*win;
	SDL_Renderer		*render;
	SDL_DisplayMode		dm;

	SDL_Init(SDL_INIT_VIDEO);
	if (!SDL_GetDesktopDisplayMode(0, &dm) && \
	(win = SDL_CreateWindow("Lem-in", 0, 0, dm.w, dm.h, \
	SDL_WINDOW_FULLSCREEN_DESKTOP)) && (render = SDL_CreateRenderer(win, -1, 0)))
	{
		venv.screen.x = dm.w;
		venv.screen.y = dm.h;
		anthill_gen(render, &venv, env);
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return (0);
	}
	return (1);
}
