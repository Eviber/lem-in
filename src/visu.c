/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/15 22:52:29 by ygaude           ###   ########.fr       */
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

t_winenv		*getsdlenv(t_room **rooms)
{
	static t_winenv	*winenv = NULL;

	if (!winenv && rooms)
		if ((winenv = (t_winenv *)malloc(sizeof(t_winenv))))
			winenv->rooms = rooms;
	return (winenv);
}

int		visu_init(t_room **rooms)
{
	t_winenv	*env;

	env = getsdlenv(rooms);
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
	SDL_SetRenderDrawColor(env->render, 50, 75, 150, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(env->render);
	return (1);
}

void	putroom(SDL_Renderer *render, t_room room)
{
	if (room.ant)
		filledCircleRGBA (render, room.pos.x * 100, room.pos.y * 100,
				30, 200, 100, 100, SDL_ALPHA_OPAQUE);
	else
		filledCircleRGBA (render, room.pos.x * 100, room.pos.y * 100,
				30, 200, 200, 200, SDL_ALPHA_OPAQUE);
}

void	putpipes(SDL_Renderer *render, t_room room)
{
	t_pos	orig;
	int		i;

	orig.x = room.pos.x * 100;
	orig.y = room.pos.y * 100;
	i = 0;
	while (room.pipes[i])
	{
		thickLineRGBA(render, orig.x, orig.y,
				room.pipes[i]->pos.x * 100, room.pipes[i]->pos.y * 100,
				10, 255, 255, 255, 50);
		i++;
	}
}

void	putrooms(SDL_Renderer *render, t_room **rooms)
{
	int		i;

	i = 0;
	while (rooms[i])
	{
		putpipes(render, *(rooms[i]));
		i++;
	}
	i = 0;
	while (rooms[i])
	{
		putroom(render, *(rooms[i]));
		i++;
	}
}

int		visu(t_room **rooms)
{
	t_winenv	*env;

	env = getsdlenv(NULL);
	if (env)
	{
		SDL_SetRenderDrawColor(env->render, 25, 37, 75, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(env->render);
		putrooms(env->render, rooms);
		SDL_RenderPresent(env->render);
	}
	return (!SDL_QuitRequested());
}

int		main(void)
{
	t_env	env;
	int		v;

	v = 1;
	env = parser();
	if (!visu_init(env.rooms))
	{
		ft_putstr_fd("Visualizer failed.\n", 2);
		v = 0;
	}
	while (v)
	{
		v = visu(env.rooms);
		if (0)
		{
			SDL_Delay(500);
			v = visu(env.rooms);
		}
	}
	return (0);
}
