/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:05 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/21 21:50:17 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include "solver.h"
#include "visu.h"

static void		reset_room(t_room **rooms)
{
	int		i;

	i = -1;
	while (rooms[++i])
	{
		if (rooms[i]->locked != -1)
			rooms[i]->prev = NULL;
		if (rooms[i]->locked != -1)
			rooms[i]->weight = 0;
		if (rooms[i]->locked != -1)
			rooms[i]->locked = 0;
		else
			rooms[i]->locked = 1;
		rooms[i]->dead = 0;
	}
}

static t_path	**addpath(t_path **oldtab)
{
	size_t				size;

	size = 0;
	while (oldtab[size])
		size++;
	oldtab[size] = ft_memalloc(sizeof(t_path));
	return (oldtab);
}

static void		clean_conflict(t_env *env)
{
	while (env->conflit->prev)
	{
		env->conflit = env->conflit->prev;
		ft_memdel((void**)&env->conflit->next);
	}
}

int				solve(t_env *env)
{
	int					i;

	i = 0;
	env->paths = (t_path **)ft_memalloc(sizeof(t_path*) * (env->nb_rooms - 1));
	env->paths = addpath(env->paths);
	while (env->nb_path < env->nb_ants && find_shortest(env, i))
	{
		env->conflict = 1;
		clean_conflict(env);
		env->paths[i++]->room->next = env->end;
		lock(env);
		reset_room(env->rooms);
		env->paths = addpath(env->paths);
	}
	if (i == 0)
	{
		ft_dprintf(2, "ERROR No path\n");
		exit(1);
	}
	lock(env);
	if (env->v)
		env->v = visu(NULL, NULL);
	return (i);
}
