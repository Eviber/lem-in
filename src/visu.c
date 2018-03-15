/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/15 09:05:45 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lemin.h"
#include "visu.h"

void				putant(t_winenv w, t_room *room, t_room *prev, int ant)
{
	Uint32			ticks;
	int				*antcolor;
	t_pos			pos;
	t_pos			lastpos;

	SDL_SetRenderTarget(w.render, w.layer[ANTS]);
	pos.x = room->pos.x * w.zoom + w.mov.x;
	pos.y = room->pos.y * w.zoom + w.mov.y;
	lastpos.x = prev->pos.x * w.zoom + w.mov.x;
	lastpos.y = prev->pos.y * w.zoom + w.mov.y;
	if ((ticks = w.frameticks + w.offticks) < w.ticks + TURNTIME)
	{
		pos.x = (double)lastpos.x + ((double)(pos.x - lastpos.x) *
			(double)(ticks - w.ticks)) / (double)TURNTIME;
		pos.y = (double)lastpos.y + ((double)(pos.y - lastpos.y) *
			(double)(ticks - w.ticks)) / (double)TURNTIME;
	}
	antcolor = (int[4]){0xFF5069FF, 0xFFD161A0, 0xFFDB8041, 0xFF7FC433};
	filledCircleColor(w.render, pos.x, pos.y, 10, antcolor[ant % 4]);
}

void				counter(t_env colony, t_winenv env)
{
	SDL_Rect		rect;
	char			*str;

	rect = (SDL_Rect){0, 0, 0, 0};
	asprintf(&str, "at start: %2zu", colony.antleft);
	putcount(env, str, &rect);
	rect.y = rect.h;
	asprintf(&str, "arrived: %3zu", env.visu_out);
	putcount(env, str, &rect);
}

void				cleartex(SDL_Renderer *render, SDL_Texture *tex)
{
	SDL_SetRenderTarget(render, tex);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
	SDL_RenderClear(render);
}

void				visu_putall(SDL_Renderer *render, t_env colony, t_winenv *w)
{
	t_room			**rooms;
	int				i;

	i = 0;
	rooms = colony.rooms;
	while (rooms[i])
	{
		if (w->redraw)
		{
			if (rooms[i]->pipes)
				putpipes(render, *(rooms[i]), *w);
			putroom(*w, rooms[i], colony);
		}
		if (!w->debug && rooms[i] && rooms[i]->prev && rooms[i]->ant)
			putant(*w, rooms[i], rooms[i]->prev, rooms[i]->ant);
		i++;
	}
	if (!w->debug)
		putlast(w, colony);
	w->redraw = w->debug;
}

int					visu(t_room *room)
{
	t_winenv		*env;

	env = getsdlenv(NULL);
	env->head = room;
	env->colony->end->prev = NULL;
	env->ticks = SDL_GetTicks();
	env->frameticks = env->ticks;
	env->offticks = 0;
	while (!handle_event(env) && env->frameticks + env->offticks - env->ticks <
								(TURNTIME * (!env->debug)) + env->wait)
	{
		if (env)
		{
			env->frameticks = SDL_GetTicks();
			SDL_SetRenderDrawColor(env->render, 0, 0, 0, 20);
			SDL_RenderClear(env->render);
			SDL_SetRenderDrawBlendMode(env->render, SDL_BLENDMODE_NONE);
			visu_update(env->render, *(env->colony), env);
			SDL_RenderPresent(env->render);
		}
	}
	env->visu_out = env->colony->lem_out;
	if (!env->quit && !env->debug)
		updatelast(env, *(env->colony));
	return (quitvisu(env));
}
