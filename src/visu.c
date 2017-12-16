/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/16 23:02:14 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "../libft/libft.h"
#include "../include/lem-in.h"
#include "../include/visu.h"

int		panic(const char *str, const char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	return (0);
}

/*
** Bourrin du cul
*/

t_env	parser(void)
{
	t_env	env;
	t_room	**ret;
	t_room	*rooms;
	t_room	**tmp;

	rooms = (t_room *)malloc(sizeof(t_room) * 8);
	tmp = (t_room **)malloc(sizeof(t_room *) * 3);
	tmp[0] = &rooms[4];
	tmp[1] = &rooms[6];
	tmp[2] = NULL;
	rooms[0] = (t_room){ tmp, NULL, NULL, "a", {23, 3}, 0, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[3];
	tmp[2] = NULL;
	rooms[1] = (t_room){ tmp, NULL, NULL, "b", {16, 7}, 0, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[1];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[7];
	tmp[3] = NULL;
	rooms[2] = (t_room){ tmp, NULL, NULL, "c", {16, 3}, 2, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[1];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[5];
	tmp[3] = NULL;
	rooms[3] = (t_room){ tmp, &rooms[4], &rooms[1], "d", {16, 5}, 0, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 5);
	tmp[0] = &rooms[0];
	tmp[1] = &rooms[2];
	tmp[2] = &rooms[3];
	tmp[3] = &rooms[7];
	tmp[4] = NULL;
	rooms[4] = (t_room){ tmp, &rooms[0], &rooms[3], "e", {9, 3}, 5, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[3];
	tmp[2] = &rooms[6];
	tmp[3] = NULL;
	rooms[5] = (t_room){ tmp, NULL, NULL, "f", {1, 5}, 3, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[0];
	tmp[1] = &rooms[5];
	tmp[2] = &rooms[7];
	tmp[3] = NULL;
	rooms[6] = (t_room){ tmp, NULL, NULL, "g", {4, 8}, 0, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[6];
	tmp[3] = NULL;
	rooms[7] = (t_room){ tmp, NULL, NULL, "h", {9, 5}, 0, 0, 0 };
	ret = (t_room **)malloc(sizeof(t_room *) * 9);
	ret[0] = &rooms[0];
	ret[1] = &rooms[1];
	ret[2] = &rooms[2];
	ret[3] = &rooms[3];
	ret[4] = &rooms[4];
	ret[5] = &rooms[5];
	ret[6] = &rooms[6];
	ret[7] = &rooms[7];
	ret[8] = NULL;
	env.rooms = ret;
	env.start = &rooms[1];
	env.end = &rooms[0];
	env.nb_ants = 12;
	env.antleft = 12;
	return (env);
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
	if (env->dispmode.w * 3 / 4 / (max.x - min.x) < env->dispmode.h * 3 / 4 / (max.y - min.y))
		env->zoom = env->dispmode.w * 3 / 4 / (max.x - min.x);
	else
		env->zoom = env->dispmode.h * 3 / 4 / (max.y - min.y);
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
		env->mov = (t_pos){env->dispmode.w / 2, env->dispmode.h / 2};
	if (env)
	{
		SDL_SetRenderDrawColor(env->render, 9, 11, 16, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(env->render);
		putrooms(env->render, *(env->colony), *env);
		SDL_RenderPresent(env->render);
	}
	return (env && !SDL_QuitRequested());
}

int		main(void)
{
	t_env	env;
	int		v;

	v = 1;
	env = parser();
	if (!visu_init(&env))
	{
		ft_putstr_fd("Visualizer failed.\n", 2);
		v = 0;
	}
	while (v)
	{
		v = visu();
		if (0)
		{
			SDL_Delay(500);
			v = visu();
		}
	}
	return (0);
}
