/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:05 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/15 14:13:21 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemin.h"
#include "visu.h"

static size_t			tabsize(void **tab)
{
	size_t				i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

static void				**tab_real(void **oldtab, size_t unitsize)
{
	void				**ret;
	size_t				size;
	size_t				new_size;

	size = tabsize(oldtab);
	new_size = sizeof(void *) * (size + 2);
	ret = ft_memalloc(new_size);
	if (ret)
	{
		if (oldtab)
			ft_memcpy(ret, oldtab, sizeof(void *) * size);
		ret[size] = ft_memalloc(unitsize);
		ft_memdel((void **)&oldtab);
		if (ret[size])
			return (ret);
	}
	return (NULL);
}

void	clean_conflict(t_env *env)
{
	while (env->conflit->prev)
	{
		env->conflit = env->conflit->prev;
		ft_memdel((void**)&env->conflit->next);
	}
}

static int	search_conf(int set, int new_dp, t_env *env)
{
	t_conflict *tmp;
	unsigned long mean_len;
	long conflit;
	int			t;

	t = set;
	tmp = env->conflit;
	conflit = env->conflict;
	mean_len = env->mean_len + new_dp;
	while(set)
	{
		while (set != tmp->state)
			tmp = tmp->prev;
		set = tmp->state - 1;
		mean_len = mean_len - tmp->old_len + tmp->new_len;
		}
	tmp = env->conflit;
	if ((float)mean_len / (env->nb_path + 1) <= (float)env->mean_len / env->nb_path)
	{
		set = t;
		while(set)
		{
			while (set != tmp->state)
				tmp = tmp->prev;
			tmp->old_room->prev = tmp->miss_direction;
			set = tmp->state - 1;
		}
		return (TRUE);
	}
	return (FALSE);
}


int			save_info(int set, int new_dp, t_room *room, t_env *env)
{
	if (set == -2)
	{
		env->conflit->new_len = new_dp;
		env->conflit->old_room = room;
		env->conflit->next = ft_memalloc(sizeof(t_conflict));
		env->conflit->next->prev = env->conflit;
		env->conflit->state = env->conflict - 1;
		env->conflit = env->conflit->next;
	}
	else if (set == -1)
		env->conflit->prev->miss_direction = room;
	else if (set == 0)
	{
		env->conflit->prev->old_len = new_dp;
	}
	else if (set > 0)
		return (search_conf(--set, new_dp, env));
	return (FALSE);
}

void					lock_path(t_env *env)
{
	t_room				*room;
	int					len;
	int					i;

	env->antleft = env->nb_ants;
	i = 0;
	env->nb_path = 0;
	env->mean_len = env->nb_ants;
	while (env->paths[i] && env->paths[i]->room)
	{
		room = env->paths[i]->room;
		len = 1;
		room->next = env->end;
		while (room && room->prev)
		{
			room->prev->next = room;
			room->locked = -1;
			room = room->prev;
			len++;
		}
		env->nb_path++;
		env->paths[i]->length = len;
		env->antleft -= len;
		i++;
		len = -1;
		while(room && room->next)
		{
			room->weight = ++len;
			room = room->next;
		}
		env->mean_len += len;

	}
}

void					reset_room(t_env *env)
{
	int					i;

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

void			conflict(t_room *r, t_env *env, long depth, t_room *r_conf)
{
	long	dp;
	long	tmp_dp;
	t_room	*tmp;

	tmp = r;
	while (tmp->next != env->end)
		tmp = tmp->next;
	dp = tmp->weight;
	tmp_dp = depth + 1;
	tmp = r->prev;
	++env->conflict;
	while (tmp->prev)
	{
		visu(tmp, tmp->prev);
		tmp->locked = env->conflict;
		tmp->weight = --tmp_dp;
		tmp = tmp->prev;
	}
	env->depth = tmp_dp - 1;
	depth = depth + 1 - r->weight + dp;
	r->dead = 1;
	save_info(-2, depth, r, env);
	save_info(-1, depth, r_conf, env);
	save_info(0, dp, r_conf, env);
}

static int				fill_weight(t_env *env, t_room *room)
{
	int					i;

	i = 0;
	while (room->pipes && room->pipes[i])
	{
		if (room->pipes[i] == env->end)
		{
			if (room->locked == 0
			|| save_info(room->locked, room->weight - 1, NULL, env))
				return (TRUE);
		}
		if (!room->pipes[i]->weight && room->pipes[i] != env->start
		&& (room->pipes[i]->locked != 1 || room == env->start))
		{
			room->pipes[i]->weight = room->weight + 1;
			room->pipes[i]->prev = room;
			room->pipes[i]->locked = room->locked;
		}
		if (room != env->start && room->pipes[i]->locked == 1)
			if (!room->pipes[i]->dead && room->locked != 1)
			{
				conflict(room->pipes[i], env, room->weight, room);
				visu(room, room->pipes[i]);
				return (FALSE);
			}
		visu(room, room->pipes[i]);
		i++;
	}
	return (FALSE);
}

t_room					*try_path(t_env *env, int depth)
{
	t_room				*cur;
	int					i;

	i = 0;
	while (env->rooms[i])
	{
		cur = env->rooms[i++];
		if (cur->weight == depth - 1 && cur->locked != 1
		&& (cur->weight || cur == env->start))
		{
			if (fill_weight(env, cur))
				return (cur);
		}
	}
	return (NULL);
}

int						find_shortest(t_env *env, int f_iter)
{
	t_room				*tmp;
	static t_room		*f_room = NULL;

	env->depth = 1;
	while (env->depth <= env->nb_rooms - 1
	&& (f_iter == 0 || env->depth < env->nb_ants + 1))
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

void					solve(t_env *env)
{
	int					i;

	i = 0;
	env->paths = (t_path **)tab_real((void **)env->paths, sizeof(t_path));
	while (find_shortest(env, i))
	{
		env->conflict = 1;
		clean_conflict(env);
		env->paths[i]->room->next = env->end;
		i++;
		lock_path(env);
		reset_room(env);
		env->paths = (t_path **)tab_real((void **)env->paths, sizeof(t_path));
	}
	if (i == 0)
	{
		ft_dprintf(2, "ERROR No path\n");
		exit(1);
	}
	lock_path(env);
	visu(NULL, NULL);
}
