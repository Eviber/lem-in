/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:31:53 by ygaude            #+#    #+#             */
/*   Updated: 2018/04/20 18:26:28 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "lemin.h"
#include "visu.h"

static int			sdl_init(t_env *colony, t_winenv **w)
{
	*w = getsdlenv(colony);
	if (!*w || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		return (panic("Error while initializing SDL: ", SDL_GetError()));
	if (SDL_GetDesktopDisplayMode(0, &((*w)->dispmode)))
		return (panic("SDL_GetDesktopDisplayMode failed: ", SDL_GetError()));
	(*w)->win = SDL_CreateWindow("lem-in",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				(*w)->dispmode.w, (*w)->dispmode.h, SDL_WINDOW_FULLSCREEN);
	if (!(*w)->win)
		return (panic("Error while creating window: ", SDL_GetError()));
	(*w)->render = SDL_CreateRenderer((*w)->win, -1, SDL_RENDERER_ACCELERATED);
	if (!(*w)->render)
		return (panic("Error while creating renderer: ", SDL_GetError()));
	return (1);
}

static int			texinit(t_winenv *w)
{
	w->layer[TUBES] = SDL_CreateTexture(w->render, SDL_PIXELFORMAT_RGBA8888,
						TARGET, w->dispmode.w, w->dispmode.h);
	w->layer[ROOMS] = SDL_CreateTexture(w->render, SDL_PIXELFORMAT_RGBA8888,
						TARGET, w->dispmode.w, w->dispmode.h);
	w->layer[ANTS] = SDL_CreateTexture(w->render, SDL_PIXELFORMAT_RGBA8888,
						TARGET, w->dispmode.w, w->dispmode.h);
	w->layer[ANT] = SDL_CreateTexture(w->render, SDL_PIXELFORMAT_RGBA8888,
						TARGET, w->dispmode.w, w->dispmode.h);
	if (!w->layer[ANT] || !w->layer[TUBES] ||
		!w->layer[ROOMS] || !w->layer[ANTS])
		return (panic("Error while creating layers: ", SDL_GetError()));
	if (TTF_Init() == -1 || !(w->font = TTF_OpenFont("minecraft.ttf", 18)) ||
							!(w->bigfont = TTF_OpenFont("chargen.ttf", 48)))
		return (panic("Error while initializing SDL_TTF: ", TTF_GetError()));
	SDL_SetTextureBlendMode(w->layer[ROOMS], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(w->layer[ANTS], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(w->layer[ANT], SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(w->render, 9, 11, 16, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(w->render);
	return (1);
}

static void			minmaxing(t_pos *min, t_pos *max, t_pos pos)
{
	if (pos.x < min->x)
		min->x = pos.x;
	else if (pos.x > max->x)
		max->x = pos.x;
	if (pos.y < min->y)
		min->y = pos.y;
	else if (pos.y > max->y)
		max->y = pos.y;
}

static void			pos_init(t_env *colony, t_winenv *w)
{
	t_pos			min;
	t_pos			max;
	int				i;

	min = colony->rooms[0]->pos;
	max = min;
	i = 0;
	while (((colony->rooms)[++i]))
		minmaxing(&min, &max, colony->rooms[i]->pos);
	i = -1;
	while (((colony->rooms)[++i]))
	{
		colony->rooms[i]->pos.x -= min.x + (max.x - min.x) / 2;
		colony->rooms[i]->pos.y -= min.y + (max.y - min.y) / 2;
	}
	max.x = max.x - min.x + !(max.x - min.x);
	max.y = max.y - min.y + !(max.y - min.y);
	w->zoom = (w->dispmode.w * 3 / 4 / max.x < w->dispmode.h * 3 / 4 / max.y) ?
			(double)w->dispmode.w * 3.0 / 4.0 / (double)max.x :
			(double)w->dispmode.h * 3.0 / 4.0 / (double)max.y;
	w->orig_zoom = w->zoom + !(w->zoom);
	w->mov = (t_pos){w->dispmode.w / 2, w->dispmode.h / 2};
}

int					visu_init(t_env *colony)
{
	t_winenv		*env;

	if (!sdl_init(colony, &env))
		return (0);
	if (!texinit(env))
		return (0);
	pos_init(colony, env);
	return (1);
}
