/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/31 19:57:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static int		get_texture(SDL_Renderer *render, SDL_Texture **texture)
{
	SDL_Surface		*surface;

	if (!(surface = SDL_LoadBMP("src/visu/dirt.bmp")))
		return (1);
	if (!(*texture = SDL_CreateTextureFromSurface(render, surface)))
		return (1);
	SDL_FreeSurface(surface);
	return (0);
}

static int		anthill_gen(SDL_Renderer *render, t_visu *venv, t_env *env)
{
	SDL_Texture		*bg;
	SDL_Rect		bg_pos;

	bg_pos.x = 0;
	bg_pos.y = -4;
	bg_pos.w = venv->screen.x;
	bg_pos.h = venv->screen.y + 4;
	if (get_texture(render, &bg))
		return (1);
	get_default_zoom(env->rooms, venv);
	if (!(venv->kb_state = SDL_GetKeyboardState(NULL)))
		return (1);
	while (!SDL_QuitRequested() && !venv->kb_state[SDL_SCANCODE_Q])
	{
		if (SDL_RenderClear(render) || \
		SDL_RenderCopy(render, bg, NULL, &bg_pos) || \
		draw_anthill(render, env->rooms, venv) || event_manager(render, venv))
			return (1);
		SDL_RenderPresent(render);
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
/*
static char		**get_step_list(void)
{
	char	**step_list;

	step_list = (char**)malloc(sizeof(char*) * 33);
	step_list[0] = ft_strdup("L1-2");
	step_list[1] = ft_strdup("L1-3 L2-2");
	step_list[2] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[3] = ft_strdup("L2-1 L3-3");
	step_list[4] = ft_strdup("L3-1");
	step_list[5] = ft_strdup("L1-1 L2-3 L3-2 L1-1 L2-3 L3-2 L1-1 L2-3 L3-2 L1-1 L2-3 L3-2 L1-1 L2-3 L3-2 L1-1 L2-3 L3-2 ");
	step_list[6] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[7] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[8] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[9] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[10] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[11] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[12] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[13] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[14] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[15] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[16] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[17] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[18] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[19] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[20] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[21] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[22] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[23] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[24] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[25] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[26] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[27] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[28] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[29] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[30] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[31] = ft_strdup("L1-1 L2-3 L3-2");
	step_list[32] = NULL;
//	step_list[5] = NULL;
	return (step_list);
}*/

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
		SDL_DestroyRenderer(render);
		SDL_DestroyWindow(win);
		TTF_Quit();
		SDL_Quit();
		return ;
	}
	SDL_Quit();
	ft_dprintf(2, "SDL error: %s\n", SDL_GetError());
}
