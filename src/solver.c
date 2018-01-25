/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:05 by ygaude            #+#    #+#             */
/*   Updated: 2018/01/25 19:23:46 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lem-in.h"
#include "libft.h"
/*
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
*/

static void clean_conflict(t_conflit *conflit)
{
	while(conflit->next)
		conflit = conflit->next;
	while(conflit)
	{
		free(conflit);
		conflit = conflit->prev;
	}
	conflit = ft_memalloc(sizeof(t_conflit));
}

int save_info(int set, int new_depth, t_room *o_room, t_room *n_room, t_env *env)
{
	static t_conflit *conflict = NULL;

	if (set == 0)
	{
		if (!conflict)
			conflict = ft_memalloc(sizeof(t_conflit));
		conflict->len = new_depth;
		conflict->old_room = o_room;
		conflict->miss_direction = n_room;
		conflict->next = ft_memalloc(sizeof(t_conflit));
		conflict->next->prev = conflict;
		conflict = conflict->next;
	}
	else
	{
		while((set++ - env->conflict) <= 1)
			conflict = conflict->prev;
		if (env->antleft >= conflict->len && env->antleft >= new_depth)
		{
			conflict->old_room->prev = conflict->miss_direction;
			clean_conflict(conflict);
			return(TRUE);
		}
		clean_conflict(conflict);
	}

	return(FALSE);
}

void lock_path(t_env *env)
{
	t_room	*room;
	int		len;
	int		i;

	env->antleft = env->nb_ants;
	i = 0;
	while(env->paths[i] && env->paths[i]->room)
	{
		room = env->paths[i]->room;
		len = 1;
		room->next = env->end;
		while(room && room->prev)
		{
			room->prev->next = room;
			room->locked = -1;
			room = room->prev;
			len++;
		}
		env->paths[i]->length = len;
		env->antleft -= len;
		i++;
	}
}

void reset_room(t_env *env)
{
	int i;

	i = -1;
	while (env->rooms[++i])
	{
		if (env->rooms[i]->locked != -1)
			env->rooms[i]->weight = 0;
		if (env->rooms[i]->locked != -1)
			env->rooms[i]->locked = 0;
		else
			env->rooms[i]->locked = 1;
		env->rooms[i]->dead = 0;
	}
}

void conflit(t_room *rooms, t_env *env, long depth, t_room *room_confict)
{
	long	dp;
	long tmp_dp;
	t_room *tmp;

	tmp = rooms;
	while(tmp->next != env->end)
		tmp = tmp->next;
	dp = tmp->weight;
	env->antleft += dp;
	tmp_dp = depth + 1;
	tmp = rooms->prev;
	++env->conflict;
	while(tmp->prev)
	{
		tmp->locked = env->conflict ;
		tmp->weight = --tmp_dp;
		tmp = tmp->prev;
	}
	env->depth = tmp_dp;
	depth = depth + 1 - rooms->weight + dp;
	rooms->dead = 1;
	save_info(0, depth, rooms, room_confict, env);
}

static int		fill_weight(t_env *env, t_room *room)
{
	int		i;

	i = 0;
	while (room->pipes && room->pipes[i])
	{
		if (room->pipes[i] == env->end)
		{
			if (room->locked == 0 || save_info(room->locked, room->weight +1, NULL, NULL, env))
				return (TRUE);
		}
		if (!room->pipes[i]->weight && room->pipes[i] != env->start && (room->pipes[i]->locked != 1 || room == env->start))
		{
			room->pipes[i]->weight = room->weight + 1;
			room->pipes[i]->prev = room;
			room->pipes[i]->locked = room->locked;
		}
		if (room != env->start && room->pipes[i]->locked == 1 && !room->pipes[i]->dead && !room->locked)
			conflit(room->pipes[i], env, room->weight, room);
		i++;
	}
	return (FALSE);
}

t_room	*try_path(t_env *env, int depth)
{
	t_room	*cur;
	int		i;

	i = 0;
	while (env->rooms[i])
	{
		cur = env->rooms[i++];
		if (cur->weight == depth - 1 && cur->locked != 1 && (cur->weight || cur == env->start))
			if (fill_weight(env, cur))
				return (cur);
	}
	return (NULL);
}

int				find_shortest(t_env *env, int f_iter)
{
	t_room *tmp;
	static t_room *f_room = NULL;

	env->depth = 1;
	while (env->depth <= env->nb_rooms - 1 && (f_iter == 0 || env->depth < env->nb_ants + 1))
	{
		if ((tmp = try_path(env, env->depth++)))
			if (tmp != f_room)
			{
				if (!f_room)
					f_room = tmp;
				if (!env->paths[f_iter]->room)
					env->paths[f_iter]->room = tmp;
				return (TRUE);
			}
	}
	return (FALSE);
}

static size_t	tabsize(void *tab)
{
	size_t	i;

	i = 0;
	while (tab++)
		i++;
	return (i);
}

static t_path	**addpath(t_path **oldpaths)
{
	t_path			**ret;
	size_t			size;
	size_t			new_size;

	size = tabsize((void *)oldpaths);
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
			ft_memcpy(ret, oldpaths, sizeof(t_path *) * size);
			ret[size] = (t_path *)ft_memalloc(sizeof(t_path));
			ft_memdel((void **)&oldpaths);
			if (ret[size])
				return (ret);
		}
	}
	return (NULL);
}

void			solve(t_env *env)
{
	int		i;

	i = 0;
	env->paths = addpath(env->paths);
	while (find_shortest(env, i))
	{
		env->conflict = 1;
		env->paths[i]->room->next = env->end;
		i++;
		lock_path(env);
		reset_room(env);
		env->paths = addpath(env->paths);
	}
	lock_path(env);
}
