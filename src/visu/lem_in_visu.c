/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/25 22:38:11 by vsporer          ###   ########.fr       */
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

	bg_pos.x = 0;
	bg_pos.y = -4;
	bg_pos.w = venv->screen.x;
	bg_pos.h = venv->screen.y + 4;
	get_texture(render, &bg);
	get_default_zoom(env->rooms, venv);
	venv->kb_state = SDL_GetKeyboardState(NULL);
	while (!SDL_QuitRequested() && !venv->kb_state[SDL_SCANCODE_Q])
	{
		SDL_RenderClear(render);
		SDL_RenderCopy(render, bg, NULL, &bg_pos);
		draw_anthill(render, env->rooms, venv);
		event_manager(render, venv);
		SDL_RenderPresent(render);
	}
	SDL_DestroyTexture(bg);
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

static char		**get_step_list(void)
{
	char	**step_list;

	step_list = (char**)malloc(sizeof(char*) * 6);
	step_list[0] = ft_strdup("L1-2");
	step_list[1] = ft_strdup("L1-3 L2-2");
	step_list[2] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[3] = ft_strdup("L2-1 L3-3");
	step_list[4] = ft_strdup("L3-1");
	step_list[5] = NULL;
	return (step_list);
}

int				lem_in_visu(t_env *env)
{
	t_visu				venv;
	SDL_Window			*win;
	SDL_Renderer		*render;
	SDL_DisplayMode		dm;

	venv.step_list = get_step_list();
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) && \
	!SDL_GetDesktopDisplayMode(0, &dm) && (win = SDL_CreateWindow("Lem-in", \
	0, 0, dm.w, dm.h, SDL_WINDOW_FULLSCREEN_DESKTOP)) && \
	(render = SDL_CreateRenderer(win, -1, 0)) && !TTF_Init())
	{
		if (!display_init(render, dm, &venv))
			anthill_gen(render, &venv, env);
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(win);
		TTF_Quit();
		SDL_Quit();
		return (0);
	}
	ft_dprintf(2, "Error start SDL failed: %s\n", SDL_GetError());
	return (1);
}
