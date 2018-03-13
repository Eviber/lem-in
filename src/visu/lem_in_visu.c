/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/06 16:19:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static int		get_texture(SDL_Renderer *render, SDL_Texture **texture, \
SDL_Rect *bg_pos, t_visu *venv)
{
	SDL_Surface		*surface;

	if (!(surface = SDL_LoadBMP("src/visu/dirt.bmp")))
		return (1);
	if (!(*texture = SDL_CreateTextureFromSurface(render, surface)))
		return (1);
	SDL_FreeSurface(surface);
	bg_pos->x = 0;
	bg_pos->y = -5;
	bg_pos->w = venv->screen.x;
	bg_pos->h = venv->screen.y + 5;
	return (0);
}

static int		anthill_gen(SDL_Renderer *render, t_visu *venv, t_env *env)
{
	SDL_Rect		bg_pos;
	SDL_Texture		*bg;
	static Uint32	ticks = 0;

	if (get_texture(render, &bg, &bg_pos, venv))
		return (1);
	get_default_zoom(env->rooms, venv);
	if (!(venv->kb_state = SDL_GetKeyboardState(NULL)))
		return (1);
	while (!SDL_QuitRequested() && !venv->kb_state[SDL_SCANCODE_Q])
	{
		if (ticks + 16 <= SDL_GetTicks())
		{
			if (SDL_RenderClear(render) || \
			SDL_RenderCopy(render, bg, NULL, &bg_pos) || draw_anthill(render, \
			env->rooms, venv) || event_manager(render, venv))
				return (1);
			SDL_RenderPresent(render);
			ticks = SDL_GetTicks();
		}
	}
	SDL_DestroyTexture(bg);
	return (0);
}

static int		display_init(SDL_Renderer *render, SDL_DisplayMode dm, \
t_visu *venv)
{
	venv->screen.x = dm.w;
	venv->screen.y = dm.h;
	venv->txt_c.r = 200;
	venv->txt_c.g = 200;
	venv->txt_c.b = 200;
	venv->txt_c.a = 255;
	venv->i = 0;
	venv->step_size.y = 0;
	if (!(venv->font = TTF_OpenFont("src/visu/game_over.ttf", 50)))
		return (1);
	if (help_display_init(render, venv))
		return (1);
	if (step_display_init(render, venv))
		return (1);
	if (!venv->help)
		return (1);
	return (0);
}

void			lem_in_visu(t_env *env)
{
	t_visu				venv;
	SDL_Window			*win;
	SDL_Renderer		*render;
	SDL_DisplayMode		dm;

	venv.step_list = env->result;
	venv.rooms = env->rooms;
	venv.start = env->start;
	venv.end = env->end;
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) && \
	!SDL_GetDesktopDisplayMode(0, &dm) && (win = SDL_CreateWindow("Lem-in", \
	0, 0, dm.w, dm.h, SDL_WINDOW_FULLSCREEN_DESKTOP)) && \
	(render = SDL_CreateRenderer(win, -1, 0)) && !TTF_Init())
	{
		if (!(!display_init(render, dm, &venv) && \
		!anthill_gen(render, &venv, env)))
			ft_dprintf(2, "SDL error: %s\n", SDL_GetError());
		clean_venv(win, render, &venv);
		return ;
	}
	SDL_Quit();
	ft_dprintf(2, "SDL error: %s\n", SDL_GetError());
}
