/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/09 19:47:39 by ygaude           ###   ########.fr       */
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
			panic("Malloc error\n", "");
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

void				putroom(t_winenv w, t_room *room, t_env colony)
{
	t_pos			pos;
	SDL_Texture		*tex;

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
	SDL_Rect	dst;
	SDL_GetMouseState(&dst.x, &dst.y);
	if ((w.putnames || dist(dst.x, dst.y, pos.x, pos.y) < 100) &&
		(tex = strtotex(room->name, w, (SDL_Color){255, 255, 255, 255})))
	{
		dst.x = pos.x;
		dst.y = pos.y;
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(w.render, tex, NULL, &dst);
		SDL_DestroyTexture(tex);
	}
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

void				counter(SDL_Renderer *render, t_env colony, t_winenv *env)
{
	SDL_Texture		*tex;
	SDL_Surface		*surf;
	SDL_Rect		rect;
	char			str[40];
	int				i;

	rect = (SDL_Rect){0, 0, 0, 0};
	sprintf(str, "at start: %2zu", colony.antleft);
	surf = TTF_RenderText_Blended(env->bigfont, str, (SDL_Color){255, 255, 255, 255});
	tex = SDL_CreateTextureFromSurface(render, surf);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(render, tex, NULL, &rect);
	rect.y = rect.h;
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
	i = 0;
	while (env->lastants && env->lastants[i])
		i++;
	sprintf(str, "arrived: %3zu", colony.lem_out - i);
	surf = TTF_RenderText_Blended(env->bigfont, str, (SDL_Color){255, 255, 255, 255});
	tex = SDL_CreateTextureFromSurface(render, surf);
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(render, tex, NULL, &rect);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(tex);
}

void				visu_update(SDL_Renderer *render, t_env colony, t_winenv *w)
{
	t_room			**rooms;
	int				i;

	i = 0;
	rooms = colony.rooms;
	SDL_SetRenderTarget(render, w->layer[TUBES]);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
	SDL_RenderClear(render);
	SDL_SetRenderTarget(render, w->layer[ROOMS]);
	iSDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(render);
	SDL_RenderFillRect(render, NULL);
	SDL_SetRenderTarget(render, w->layer[ANTS]);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);
	SDL_RenderFillRect(render, NULL);
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
	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, w->layer[TUBES], NULL, NULL);
	SDL_RenderCopy(render, w->layer[ROOMS], NULL, NULL);
	SDL_RenderCopy(render, w->layer[ANTS], NULL, NULL);
	counter(render, colony, w);
}

int					visu(void)
{
	t_winenv		*env;

	env = getsdlenv(NULL);
	env->ticks = SDL_GetTicks();
	env->frameticks = env->ticks;
	env->offticks = 0;
	while (!handle_event(env) && env->frameticks + env->offticks - env->ticks < TURNTIME + env->wait)
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
