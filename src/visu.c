/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/21 00:21:30 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lem-in.h"
#include "visu.h"

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
		if ((winenv = (t_winenv *)malloc(sizeof(t_winenv))))
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
	if (env->dispmode.w * 3 / 4 / (max.x - min.x + !(max.y - min.y)) < env->dispmode.h * 3 / 4 / (max.y - min.y + !(max.y - min.y)))
		env->zoom = env->dispmode.w * 3 / 4 / (max.x - min.x + !(max.y - min.y));
	else
		env->zoom = env->dispmode.h * 3 / 4 / (max.y - min.y + !(max.y - min.y));
	env->orig_zoom = env->zoom;
	env->mov = (t_pos){env->dispmode.w / 2, env->dispmode.h / 2};
	return (1);
}

void	putroom(SDL_Renderer *render, t_room *room, t_env colony, t_winenv w)
{
	t_pos	pos;

	pos.x = room->pos.x * w.zoom + w.mov.x;
	pos.y = room->pos.y * w.zoom + w.mov.y;
	filledCircleColor(render, pos.x, pos.y, 33, 0xFF78726F);
	if (room == colony.start && room == colony.end)
		filledCircleRGBA (render, pos.x, pos.y,
				30, 200, 200, 200, SDL_ALPHA_OPAQUE);
	else if (room == colony.start)
		filledCircleColor(render, pos.x, pos.y, 30, 0xFFBCBA00);
	else if (room == colony.end)
		filledCircleRGBA (render, pos.x, pos.y,
				30, 200, 200, 100, SDL_ALPHA_OPAQUE);
	else
		filledCircleColor(render, pos.x, pos.y, 30, 0xFF4C4846);
	if (room->ant)
	{
		if (room->ant % 4 == 1)
			filledCircleColor(render, pos.x, pos.y, 10, 0xFFD161A0);
		else if (room->ant % 4 == 2)
			filledCircleColor(render, pos.x, pos.y, 10, 0xFFDB8041);
		else if (room->ant % 4 == 3)
			filledCircleColor(render, pos.x, pos.y, 10, 0xFF7FC433);
		else
			filledCircleColor(render, pos.x, pos.y, 10, 0xFF5069FF);
	}
}

void	putpipes(SDL_Renderer *render, t_room room, t_winenv w)
{
	t_pos	orig;
	t_pos	dest;
	int		i;
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

void	putrooms(SDL_Renderer *render, t_env colony, t_winenv w)
{
	t_room	**rooms;
	int		i;

	i = 0;
	rooms = colony.rooms;
	while (rooms[i])
	{
		if (rooms[i]->pipes)
			putpipes(render, *(rooms[i]), w);
		i++;
	}
	i = 0;
	while (rooms[i])
	{
		putroom(render, rooms[i], colony, w);
		i++;
	}
}

int		visu(void)
{
	t_winenv	*env;
	const Uint8	*state;

	env = getsdlenv(NULL);
	state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_KP_PLUS])
	{
		env->mov.x = env->dispmode.w / 2 +
		(long)(env->mov.x - env->dispmode.w / 2) * (env->zoom + 1) / env->zoom;
		env->mov.y = env->dispmode.h / 2 +
		(long)(env->mov.y - env->dispmode.h / 2) * (env->zoom + 1) / env->zoom;
		env->zoom++;
	}
	if (state[SDL_SCANCODE_KP_MINUS] && env->zoom > 30)
	{
		env->mov.x = env->dispmode.w / 2 +
		(long)(env->mov.x - env->dispmode.w / 2) * (env->zoom - 1) / env->zoom;
		env->mov.y = env->dispmode.h / 2 +
		(long)(env->mov.y - env->dispmode.h / 2) * (env->zoom - 1) / env->zoom;
		env->zoom--;
	}
	if (state[SDL_SCANCODE_UP])
		env->mov.y--;
	if (state[SDL_SCANCODE_DOWN])
		env->mov.y++;
	if (state[SDL_SCANCODE_LEFT])
		env->mov.x--;
	if (state[SDL_SCANCODE_RIGHT])
		env->mov.x++;
	if (state[SDL_SCANCODE_SPACE])
	{
		env->mov = (t_pos){env->dispmode.w / 2, env->dispmode.h / 2};
		env->zoom = env->orig_zoom;
	}
	if (env)
	{
		SDL_SetRenderDrawColor(env->render, 9, 11, 16, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(env->render);
		putrooms(env->render, *(env->colony), *env);
		SDL_RenderPresent(env->render);
	}
	SDL_Delay(500);
	return (env && !SDL_QuitRequested());
}
