/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:05 by ygaude            #+#    #+#             */
/*   Updated: 2018/01/18 00:08:41 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"
#include "libft.h"

static int		fill_weight(const t_env *env, t_room *room)
{
	int		i;

	i = 0;
	while (room && room->pipes && room->pipes[i])
	{
		if (room->pipes[i] == env->end)
			return (TRUE);
		if (!room->pipes[i]->weight && !room->pipes[i]->locked && room->pipes[i] != env->start)
		{
			room->pipes[i]->weight = room->weight + 1;
			room->pipes[i]->prev = room;
		}
		i++;
	}
	return (FALSE);
}

static t_room	*try_path(t_env *env, int depth)
{
	t_room	*cur;
	int		i;

	i = 0;
	while (env->rooms[i])
	{
		cur = env->rooms[i++];
		if (cur->weight == depth - 1 && (cur->weight || cur == env->start))
			if (fill_weight(env, cur))
				return (cur);
	}
	return (NULL);
}

static int		find_shortest(t_env *env, int *v)
{
	int		depth;

	depth = 1;
	(void)v;
	env->paths = (t_path **)ft_memalloc(sizeof(t_path *) * 2);
	*(env->paths) = (t_path *)ft_memalloc(sizeof(t_path));
	env->paths[0]->room = env->start;
	env->paths[0]->length = 1;
	while (depth <= env->nb_rooms - 1)
	{
		if (((*(env->paths))->room = try_path(env, depth++)))
		{
			(*(env->paths))->length = (*(env->paths))->room->weight;
			return (TRUE);
		}
	}
	return (FALSE);
}

static void		lockmap(t_env *env, int *v)
{
	t_room	*cur;
	int		i;

	i = 0;
	(void)v;
	while (env->paths[i])
	{
		cur = env->paths[i]->room;
		while (cur != env->start)
		{
			cur->locked = TRUE;
			cur = cur->prev;
		}
		i++;
	}
	i = 0;
	while (env->rooms[i])
		env->rooms[i++]->weight = 0;
}

static t_path	**addpath(t_path **oldpaths, int size)
{
	t_path			**ret;
	size_t			old_size;
	size_t			new_size;

	old_size = sizeof(t_path *) * size;
	new_size = sizeof(t_path *) * (size + 2);
	if (!oldpaths)
	{
		if ((ret = (t_path **)ft_memalloc(new_size)))
			return (ret);
	}
	else
	{
		ret = (t_path **)ft_memalloc(new_size);
		if (ret)
		{
			ft_memcpy(ret, oldpaths, old_size);
			ret[size] = (t_path *)ft_memalloc(sizeof(t_path));
			ft_memdel((void **)&oldpaths);
			if (ret[size])
				return (ret);
		}
	}
	return (NULL);
}

static t_room	*try_fulker(t_env *env, int depth)
{
	t_room	*cur;
	int		i;

	i = 0;
	while (env->rooms[i])
	{
		cur = env->rooms[i++];
		if (cur->weight == depth - 1 && (cur->weight || cur == env->start) && !cur->locked)
			if (fill_weight(env, cur))
				return (cur);
	}
	return (NULL);
}

int		iter_fulkerson(t_env *env, int npaths, int *v)
{
	int		depth;

	depth = 1;
	(void)v;
	env->paths = addpath(env->paths, npaths);
	while (depth <= env->nb_rooms - 1)
	{
		if (((env->paths[npaths])->room = try_fulker(env, depth++)))
		{
			(env->paths[npaths])->length = (env->paths[npaths])->room->weight;
			return (TRUE);
		}
	}
	ft_memdel((void **)&(env->paths[npaths]));
	return (FALSE);
}

int				solve(t_env *env, int *v)
{
	int		npaths;

	if (!find_shortest(env, v))
		return (FALSE);
	lockmap(env, v);
	npaths = 1;
	while (iter_fulkerson(env, npaths, v))
	{
		lockmap(env, v);
		npaths++;
	}
	return (TRUE);
}
