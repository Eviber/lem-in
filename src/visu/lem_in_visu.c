/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/06 22:04:01 by vsporer          ###   ########.fr       */
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

static void		get_min_max(t_room **rooms, t_visu *venv)
{
	int		i;

	i = -1;
	venv->max.x = 0;
	venv->max.y = 0;
	venv->origin.x = venv->screen.x / 2;
	venv->origin.y = venv->screen.y / 2;
	while (rooms && rooms[++i])
	{
		if ((rooms[i])->pos.x > venv->max.x)
			venv->max.x = (rooms[i])->pos.x;
		if ((rooms[i])->pos.y > venv->max.y)
			venv->max.y = (rooms[i])->pos.y;
	}
	i = -1;
	venv->min = venv->max;
	while (rooms && rooms[++i])
	{
		if ((rooms[i])->pos.x < venv->min.x)
			venv->min.x = (rooms[i])->pos.x;
		if ((rooms[i])->pos.y < venv->min.y)
			venv->min.y = (rooms[i])->pos.y;
	}
	venv->morigin.x = ((venv->max.x - venv->min.x) / 2) + venv->min.x;
	venv->morigin.y = ((venv->max.y - venv->min.y) / 2) + venv->min.y;
}

static void		get_default_zoom(t_room **rooms, t_visu *venv)
{
	get_min_max(rooms, venv);
	venv->offset.x = venv->origin.x - venv->morigin.x;
	venv->offset.y = venv->origin.y - venv->morigin.y;
	venv->bzoom = 1;
	if ((venv->max.x + venv->offset.x) > (venv->screen.x - 200) || \
	(venv->max.y + venv->offset.y) > (venv->screen.y - 200))
		venv->zoommod = DIV;
	else if ((venv->max.x + venv->offset.x) < (venv->screen.x - 200) || \
	(venv->max.y + venv->offset.y) < (venv->screen.y - 200))
		venv->zoommod = MULT;
	while (((venv->max.x / venv->bzoom) - (venv->min.x / venv->bzoom)) > \
	(venv->screen.x - 200) || ((venv->max.y / venv->bzoom) - \
	(venv->min.y / venv->bzoom)) / venv->bzoom > (venv->screen.y - 200))
		venv->bzoom++;
	while (((venv->max.x * (venv->bzoom + 1)) - (venv->min.x * \
	(venv->bzoom + 1))) < (venv->screen.x - 200) && ((venv->max.y * \
	(venv->bzoom + 1)) - (venv->min.y * (venv->bzoom + 1))) < \
	(venv->screen.y - 200))
		venv->bzoom++;
	venv->morigin.x = venv->zoommod == DIV ? (((venv->max.x / venv->bzoom) - (venv->min.x / venv->bzoom)) / 2) + (venv->min.x / venv->bzoom) : (((venv->max.x * venv->bzoom) - (venv->min.x * venv->bzoom)) / 2) + (venv->min.x * venv->bzoom);
	venv->morigin.y = venv->zoommod == DIV ? (((venv->max.y / venv->bzoom) - (venv->min.y / venv->bzoom)) / 2) + (venv->min.y / venv->bzoom) : (((venv->max.y * venv->bzoom) - (venv->min.y * venv->bzoom)) / 2) + (venv->min.y * venv->bzoom);
	venv->offset.x = venv->origin.x - venv->morigin.x;
	venv->offset.y = venv->origin.y - venv->morigin.y;
/*	while ((venv->max.x - venv->min.x) * (venv->bzoom + 1) < \
	(venv->screen.x - 200) && (venv->max.y - venv->min.y) * (venv->bzoom + 1) \
	< (venv->screen.y - 200))
		venv->bzoom++;*/
/*	while (((((venv->max.x + venv->offset.x) - venv->origin.x) / \
	venv->bzoom) + venv->origin.x) > (venv->screen.x - BORDER_W) || \
	((((venv->max.y + venv->offset.y) - venv->origin.y) / venv->bzoom) + \
	venv->origin.y) > (venv->screen.y - BORDER_H))
		venv->bzoom++;
	while (((((venv->max.x + venv->offset.x) - venv->origin.x) * \
	(venv->bzoom + 1)) + venv->origin.x) < (venv->screen.x - BORDER_W) || \
	((((venv->max.y + venv->offset.y) - venv->origin.y) * (venv->bzoom + 1)) \
	+ venv->origin.y) < (venv->screen.y - BORDER_H))
		venv->bzoom++;*/
	venv->zoom = venv->bzoom;
}

static void		anthill_gen(SDL_Renderer *render, t_visu *venv, t_env *env)
{
	SDL_Texture		*bg;
	SDL_Rect		bg_pos;

	if (!env)
		return ;
	bg_pos.x = 0;
	bg_pos.y = -4;
	bg_pos.w = venv->screen.x;
	bg_pos.h = venv->screen.y + 4;
	get_texture(render, &bg);
	get_default_zoom(env->rooms, venv);
	while (!SDL_QuitRequested())
	{
		SDL_RenderClear(render);
		SDL_RenderCopy(render, bg, NULL, &bg_pos);
		get_pipes_visu(render, env->rooms, venv);
		get_rooms_visu(render, env->rooms, venv);
		SDL_RenderPresent(render);
//		sleep(1);
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
