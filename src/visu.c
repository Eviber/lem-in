/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/11 10:35:50 by ygaude           ###   ########.fr       */
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

void				updatelast(t_winenv *w, t_env colony)
{
	int				i;

	if (!w->lastants)
	{
		i = 0;
		while (colony.paths[i])
			i++;
		w->lastants = (size_t *)ft_memalloc(i * sizeof(size_t));
		if (!w->lastants)
		{
			panic("Malloc error\n", "");
			return ;
		}
	}
	i = 0;
	while (colony.paths[i] && colony.paths[i]->room)
	{
		w->lastants[i] = colony.paths[i]->room->ant;
		i++;
	}
}

void				putlast(t_winenv *w, t_env colony)
{
	int				i;

	i = 0;
	while (w->lastants && colony.paths[i])
	{
		if (w->lastants[i])
			putant(*w, colony.end, colony.paths[i]->room, w->lastants[i]);
		i++;
	}
}

void				putroomname(t_winenv w, char *roomname, t_pos pos)
{
	SDL_Rect	dst;
	SDL_Texture	*tex;

	SDL_GetMouseState(&dst.x, &dst.y);
	if ((w.putnames || dist(dst.x, dst.y, pos.x, pos.y) < 100) &&
		(tex = strtotex(roomname, w, w.font)))
	{
		dst.x = pos.x;
		dst.y = pos.y;
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(w.render, tex, NULL, &dst);
		SDL_DestroyTexture(tex);
	}
}

void				putroom(t_winenv w, t_room *room, t_env colony)
{
	t_pos			pos;

	SDL_SetRenderTarget(w.render, w.layer[ROOMS]);
	pos.x = room->pos.x * w.zoom + w.mov.x;
	pos.y = room->pos.y * w.zoom + w.mov.y;
	filledCircleColor(w.render, pos.x, pos.y, 33, 0xFF78726F);
	if (room == colony.start && room == colony.end)
		filledCircleRGBA(w.render, pos.x, pos.y, 30, 200, 200, 200,
							SDL_ALPHA_OPAQUE);
	else if (room == colony.start)
		filledCircleColor(w.render, pos.x, pos.y, 30, 0xFFBCBA00);
	else if (room == colony.end)
		filledCircleRGBA(w.render, pos.x, pos.y, 30, 200, 200, 100,
							SDL_ALPHA_OPAQUE);
	else
		filledCircleColor(w.render, pos.x, pos.y, 30, 0xFF4C4846);
	putroomname(w, room->name, pos);
}

void				putpipes(SDL_Renderer *render, t_room room, t_winenv w)
{
	t_pos			orig;
	t_pos			dest;
	int				i;

	SDL_SetRenderTarget(render, w.layer[TUBES]);
	orig.x = room.pos.x * w.zoom + w.mov.x;
	orig.y = room.pos.y * w.zoom + w.mov.y;
	i = 0;
	while (room.pipes[i])
	{
		dest.x = room.pipes[i]->pos.x * w.zoom + w.mov.x;
		dest.y = room.pipes[i]->pos.y * w.zoom + w.mov.y;
		thickLineRGBA(render, orig.x, orig.y, dest.x, dest.y,
				10, 255, 255, 255, 50);
		i++;
	}
}

void				putcount(t_winenv env, char *str, SDL_Rect *rect)
{
	SDL_Texture		*tex;

	tex = strtotex(str, env, env.bigfont);
	SDL_QueryTexture(tex, NULL, NULL, &rect->w, &rect->h);
	SDL_RenderCopy(env.render, tex, NULL, rect);
	SDL_DestroyTexture(tex);
	free(str);
}

void				counter(t_env colony, t_winenv env)
{
	SDL_Rect		rect;
	char			*str;
	int				i;

	rect = (SDL_Rect){0, 0, 0, 0};
	asprintf(&str, "at start: %2zu", colony.antleft);
	putcount(env, str, &rect);
	rect.y = rect.h;
	i = 0;
	while (env.lastants && env.lastants[i])
		i++;
	asprintf(&str, "arrived: %3zu", colony.lem_out - i);
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
		if (rooms[i]->pipes)
			putpipes(render, *(rooms[i]), *w);
		putroom(*w, rooms[i], colony);
		if (rooms[i] && rooms[i]->prev && rooms[i]->ant)
			putant(*w, rooms[i], rooms[i]->prev, rooms[i]->ant);
		i++;
	}
	putlast(w, colony);
}

void				visu_update(SDL_Renderer *render, t_env colony, t_winenv *w)
{
	cleartex(render, w->layer[TUBES]);
	cleartex(render, w->layer[ROOMS]);
	cleartex(render, w->layer[ANTS]);
	visu_putall(render, colony, w);
	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, w->layer[TUBES], NULL, NULL);
	SDL_RenderCopy(render, w->layer[ROOMS], NULL, NULL);
	SDL_RenderCopy(render, w->layer[ANTS], NULL, NULL);
	counter(colony, *w);
}

int					visu(void)
{
	t_winenv		*env;

	env = getsdlenv(NULL);
	env->ticks = SDL_GetTicks();
	env->frameticks = env->ticks;
	env->offticks = 0;
	while (!handle_event(env) &&
			env->frameticks + env->offticks - env->ticks < TURNTIME + env->wait)
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
	if (!env->quit)
		updatelast(env, *(env->colony));
	return (quitvisu(env));
}
