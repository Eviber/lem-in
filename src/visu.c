/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/14 00:17:46 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../include/lem-in.h"

void	panic(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int		atoi_next_line(int fd, int *val)
{
	int		ret;
	char	*str;

	if ((ret = get_next_line(fd, &str)) != -1)
	{
		*val = ft_atoi(str);
		ft_strdel(&str);
	}
	return (ret);
}
/*
int		parse_room(t_env *env, char *str)
{
	return (0);
}

int		parse_tube(t_env *env, char *str)
{
	return (0);
}
*/
int		whatis(char *str)
{
	if(str[0] == '#')
	{
		if (ft_strequ(str, "##start"))
			return (START);
		else if (ft_strequ(str, "##end"))
			return (END);
		else
			return (COMM);
	}
	if (ft_strchr(str, '-') && !ft_strchr(str, ' '))
		return (TUBE);
	return (ROOM);
}

/*
** Bourrin du cul
*/

t_env	parser(void)
{
	t_env	env;
	t_room	*rooms;
	t_room	**tmp;

	rooms = (t_room *)malloc(sizeof(t_room) * 8);
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[4];
	tmp[1] = &rooms[6];
	tmp[2] = NULL;
	rooms[0] = (t_room){ tmp, NULL, NULL, "a", {23, 3}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[3];
	tmp[2] = NULL;
	rooms[1] = (t_room){ tmp, NULL, NULL, "b", {16, 7}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[1];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[7];
	tmp[3] = NULL;
	rooms[2] = (t_room){ tmp, NULL, NULL, "c", {16, 3}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[1];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[8];
	tmp[3] = NULL;
	rooms[3] = (t_room){ tmp, NULL, NULL, "d", {16, 5}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 5);
	tmp[0] = &rooms[0];
	tmp[1] = &rooms[1];
	tmp[2] = &rooms[2];
	tmp[3] = &rooms[7];
	tmp[4] = NULL;
	rooms[4] = (t_room){ tmp, NULL, NULL, "e", {9, 3}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[3];
	tmp[2] = &rooms[6];
	tmp[3] = NULL;
	rooms[5] = (t_room){ tmp, NULL, NULL, "f", {1, 5}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[0];
	tmp[1] = &rooms[5];
	tmp[2] = &rooms[7];
	tmp[3] = NULL;
	rooms[6] = (t_room){ tmp, NULL, NULL, "g", {4, 8}, 0, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[6];
	tmp[3] = NULL;
	rooms[7] = (t_room){ tmp, NULL, NULL, "h", {9, 5}, 0, 0 };
	env.start = &rooms[1];
	env.end = &rooms[0];
	env.total_ants = 12;
	env.atstart = 12;
	return (env);
}

t_winenv		*getsdlenv(t_pile *p)
{
	static t_winenv	*winenv = NULL;

	if (!winenv)
		if (p && (winenv = (t_winenv *)malloc(sizeof(t_winenv))))
			winenv->max = maxvalue(p, &(winenv->pop)) + 1;
	return (winenv);
}

int				visu_init(void)
{
	t_winenv	*env;

	env = getsdlenv(NULL);
	if (!env || SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		fprintf(stderr, "Error while initializing SDL: %s\n", SDL_GetError());
		return (0);
	}
	env->win = SDL_CreateWindow("push_swap",
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
				WIN_W, WIN_H, 0);
	if (!env->win)
	{
		fprintf(stderr, "Error while creating window: %s\n", SDL_GetError());
		return (0);
	}
	env->render = SDL_CreateRenderer(env->win, -1, SDL_RENDERER_ACCELERATED);
	if (!env->render)
	{
		fprintf(stderr, "Error while creating renderer: %s\n", SDL_GetError());
		return (0);
	}
	SDL_SetRenderDrawColor(env->render, 0, 0, 0, 255);
	SDL_RenderClear(env->render);
	return (1);
}

int		main(void)
{
	t_env	env;

	env = parser();
	if (!visu_init())
		ft_putstr_fd(2, "Visualizer failed.\n");
	return (0);
}
