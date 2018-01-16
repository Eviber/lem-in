/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/01/16 18:41:18 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lem-in.h"
#include "visu.h"

#define TURNTIME 1000

int		panic(const char *str, const char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	return (0);
}

t_winenv		*getsdlenv(t_env *colony)
{
	static t_winenv	*winenv = NULL;

	if (!winenv && colony)
		if ((winenv = (t_winenv *)ft_memalloc(sizeof(t_winenv))))
			winenv->colony = colony;
	return (winenv);
}

int		visu_init(t_env *colony)
{
	t_winenv	*env;
	t_pos		min;
	t_pos		max;
	int			i;

	env = getsdlenv(colony);
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		return(panic("Error while initializing SDL: ", SDL_GetError()));
	if (SDL_GetDesktopDisplayMode(0, &(env->dispmode)))
		return(panic("SDL_GetDesktopDisplayMode failed: ", SDL_GetError()));
	env->win = SDL_CreateWindow("lem-in",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				env->dispmode.w, env->dispmode.h, 0);//SDL_WINDOW_FULLSCREEN);
	if (!env->win)
		return(panic("Error while creating window: ", SDL_GetError()));
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->render)
		return(panic("Error while creating renderer: ", SDL_GetError()));
	env->layer[TUBES] = SDL_CreateTexture(env->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, env->dispmode.w, env->dispmode.h);
	env->layer[ROOMS] = SDL_CreateTexture(env->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, env->dispmode.w, env->dispmode.h);
	env->layer[ANTS] = SDL_CreateTexture(env->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, env->dispmode.w, env->dispmode.h);
	env->layer[ANT] = SDL_CreateTexture(env->render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, env->dispmode.w, env->dispmode.h);
	if (!env->layer[TUBES] || !env->layer[ROOMS] || !env->layer[ANTS])
		return(panic("Error while creating layers: ", SDL_GetError()));
//	SDL_SetTextureBlendMode(env->layer[TUBES], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(env->layer[ROOMS], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(env->layer[ANTS], SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(env->layer[ANT], SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(env->render, 9, 11, 16, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env->render);
	min = colony->rooms[0]->pos;
	max = min;
	i = 1;
	while (((colony->rooms)[i]))
	{
		if (colony->rooms[i]->pos.x < min.x)
			min.x = colony->rooms[i]->pos.x;
		if (colony->rooms[i]->pos.y < min.y)
			min.y = colony->rooms[i]->pos.y;
		if (colony->rooms[i]->pos.x > max.x)
			max.x = colony->rooms[i]->pos.x;
		if (colony->rooms[i]->pos.y > max.y)
			max.y = colony->rooms[i]->pos.y;
		i++;
	}
	i = 0;
	while (((colony->rooms)[i]))
	{
		colony->rooms[i]->pos.x -= min.x + (max.x - min.x) / 2;
		colony->rooms[i]->pos.y -= min.y + (max.y - min.y) / 2;
		i++;
	}
	if (env->dispmode.w * 3 / 4 / (max.x - min.x + !(max.x - min.x)) < env->dispmode.h * 3 / 4 / (max.y - min.y + !(max.y - min.y)))
		env->zoom = (double)env->dispmode.w * 3.0 / 4.0 / (double)(max.x - min.x + !(max.x - min.x));
	else
		env->zoom = (double)env->dispmode.h * 3.0 / 4.0 / (double)(max.y - min.y + !(max.y - min.y));
	env->orig_zoom = env->zoom + !(env->zoom);
	env->mov = (t_pos){env->dispmode.w / 2, env->dispmode.h / 2};
	return (1);
}

void	putant(t_winenv w, t_room *room, t_room *prev, int ant)
{
	Uint32	ticks;
	int		*antcolor;
	t_pos	pos;
	t_pos	lastpos;

	SDL_SetRenderTarget(w.render, w.layer[ANTS]);
	pos.x = room->pos.x * w.zoom + w.mov.x;
	pos.y = room->pos.y * w.zoom + w.mov.y;
	lastpos.x = prev->pos.x * w.zoom + w.mov.x;
	lastpos.y = prev->pos.y * w.zoom + w.mov.y;
	if ((ticks = SDL_GetTicks()) < w.ticks + TURNTIME)
	{
		pos.x = (double)lastpos.x + ((double)(pos.x - lastpos.x) *
			(double)(ticks - w.ticks)) / (double)TURNTIME;
		pos.y = (double)lastpos.y + ((double)(pos.y - lastpos.y) *
			(double)(ticks - w.ticks)) / (double)TURNTIME;
	}
	antcolor = (int [4]){0xFF5069FF, 0xFFD161A0, 0xFFDB8041, 0xFF7FC433};
	filledCircleColor(w.render, pos.x, pos.y, 10, antcolor[ant % 4]);
}

void	updatelast(t_winenv *w, t_env colony)
{
	int		i;

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

void	putlast(t_winenv *w, t_env colony)
{
	int		i;

	i = 0;
	while (w->lastants && colony.paths[i])
	{
		if (w->lastants[i])
			putant(*w, colony.end, colony.paths[i]->room, w->lastants[i]);
		i++;
	}
}

void	putroom(t_winenv w, t_room *room, t_env colony)
{
	t_pos	pos;

	SDL_SetRenderTarget(w.render, w.layer[ROOMS]);
	pos.x = room->pos.x * w.zoom + w.mov.x;
	pos.y = room->pos.y * w.zoom + w.mov.y;
	filledCircleColor(w.render, pos.x, pos.y, 33, 0xFF78726F);
	if (room == colony.start && room == colony.end)
		filledCircleRGBA (w.render, pos.x, pos.y,
				30, 200, 200, 200, SDL_ALPHA_OPAQUE);
	else if (room == colony.start)
		filledCircleColor(w.render, pos.x, pos.y, 30, 0xFFBCBA00);
	else if (room == colony.end)
		filledCircleRGBA (w.render, pos.x, pos.y,
				30, 200, 200, 100, SDL_ALPHA_OPAQUE);
	else
		filledCircleColor(w.render, pos.x, pos.y, 30, 0xFF4C4846);
}

void	putpipes(SDL_Renderer *render, t_room room, t_winenv w)
{
	t_pos	orig;
	t_pos	dest;
	int		i;

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

void	putrooms(SDL_Renderer *render, t_env colony, t_winenv *w)
{
	t_room	**rooms;
	int		i;

	i = 0;
	rooms = colony.rooms;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_SetRenderTarget(render, w->layer[TUBES]);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
	SDL_RenderClear(render);
	SDL_SetRenderTarget(render, w->layer[ROOMS]);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
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
}

int		handle_event(t_winenv *env, Uint32 ticks)
{
	const Uint8	*state;
	double		zoomval;

	state = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	if (state[SDL_SCANCODE_KP_PLUS])
	{
		zoomval = 1.1;
		env->mov.x = env->dispmode.w / 2 +
		(long)(env->mov.x - env->dispmode.w / 2) * (env->zoom * zoomval) / env->zoom;
		env->mov.y = env->dispmode.h / 2 +
		(long)(env->mov.y - env->dispmode.h / 2) * (env->zoom * zoomval) / env->zoom;
		env->zoom *= zoomval;
	}
	if (state[SDL_SCANCODE_KP_MINUS] && env->zoom * 0.9 > 0)
	{
		zoomval = 0.9;
		env->mov.x = env->dispmode.w / 2 +
		(long)(env->mov.x - env->dispmode.w / 2) * (env->zoom * zoomval) / env->zoom;
		env->mov.y = env->dispmode.h / 2 +
		(long)(env->mov.y - env->dispmode.h / 2) * (env->zoom * zoomval) / env->zoom;
		env->zoom *= zoomval;
	}
	env->mov.y += (0.3 * ticks) * ((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
				- (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]));
	env->mov.x += (0.3 * ticks) * ((state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
				- (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]));
	if (state[SDL_SCANCODE_SPACE])
	{
		env->mov = (t_pos){env->dispmode.w / 2, env->dispmode.h / 2};
		env->zoom = env->orig_zoom;
	}
	return (state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_ESCAPE]);
}

int		quitvisu(t_winenv *env, int quit)
{
	if (!env || quit)
	{
		SDL_Quit();
		return (0);
	}
	return (1);
}

int		visu(void)
{
	t_winenv	*env;
	Uint32		frameticks;
	int			quit;

	env = getsdlenv(NULL);
	env->ticks = SDL_GetTicks();
	frameticks = env->ticks;
	while (SDL_GetTicks() - env->ticks < TURNTIME + 100 && !(quit = handle_event(env, SDL_GetTicks() - frameticks) || SDL_QuitRequested()))
	{
		if (env)
		{
			frameticks = SDL_GetTicks();
			SDL_SetRenderDrawColor(env->render, 0, 0, 0, 20);
//			SDL_SetRenderDrawBlendMode(env->render, SDL_BLENDMODE_BLEND);
//			SDL_RenderFillRect(env->render, NULL);
			SDL_RenderClear(env->render);
			SDL_SetRenderDrawBlendMode(env->render, SDL_BLENDMODE_NONE);
			putrooms(env->render, *(env->colony), env);
			SDL_RenderPresent(env->render);
		}
	}
	if (!quit)
		updatelast(env, *(env->colony));
	return (quitvisu(env, quit));
}
