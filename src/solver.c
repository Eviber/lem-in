/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:05 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/14 11:33:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemin.h"
#include "libft.h"

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

static void				clean_conflict(t_conflict *conflict)
{
	while (conflict && conflict->next)
		conflict = conflict->next;
	while (0 && conflict)
	{
		free(conflict);
		conflict = conflict->prev;
	}
	conflict = ft_memalloc(sizeof(t_conflict));
}

int						save_info(int set, int new_depth, t_room *o_room, t_room *n_room, t_env *env)
{
	static t_conflict	**conflict = NULL;
	size_t				i;

	i = tabsize((void **)conflict);
	if (set == 0)
	{
		conflict = (t_conflict **)tab_real((void **)conflict, sizeof(t_conflict));
		conflict[i]->len = new_depth;
		conflict[i]->old_room = o_room;
		conflict[i]->miss_direction = n_room;
	}
	else
	{
		if (conflict[i - (set - env->conflict) - 1] && env->antleft >= conflict[i - (set - env->conflict) - 1]->len && env->antleft >= new_depth)
		{
			conflict[i - (set - env->conflict) - 1]->old_room->prev = conflict[i - (set - env->conflict) - 1]->miss_direction;
			clean_conflict(conflict[i - (set - env->conflict) - 1]);
			return (TRUE);
		}
		clean_conflict(conflict[i - (set - env->conflict) - 1]);
	}
	return (FALSE);
}

void					lock_path(t_env *env)
{
	t_room				*room;
	int					len;
	int					i;

	env->antleft = env->nb_ants;
	i = 0;
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
		env->paths[i]->length = len;
		env->antleft -= len;
		i++;
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

void					conflict(t_room *rooms, t_env *env, long depth,
						t_room *room_confict)
{
	long				dp;
	long				tmp_dp;
	t_room				*tmp;

	tmp = rooms;
	while (tmp->next != env->end)
		tmp = tmp->next;
	dp = tmp->weight;
	env->antleft += dp;
	tmp_dp = depth + 1;
	tmp = rooms->prev;
	++env->conflict;
	while (tmp->prev)
	{
		tmp->locked = env->conflict;
		tmp->weight = --tmp_dp;
		tmp = tmp->prev;
	}
	env->depth = tmp_dp;
	depth = depth + 1 - rooms->weight + dp;
	rooms->dead = 1;
	save_info(0, depth, rooms, room_confict, env);
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
			|| save_info(room->locked, room->weight + 1, NULL, NULL, env))
				return (TRUE);
		}
		if (!room->pipes[i]->weight && room->pipes[i] != env->start
		&& (room->pipes[i]->locked != 1 || room == env->start))
		{
			room->pipes[i]->weight = room->weight + 1;
			room->pipes[i]->prev = room;
			room->pipes[i]->locked = room->locked;
		}
		if (room != env->start && room->pipes[i]->locked == 1
		&& !room->pipes[i]->dead && !room->locked)
			conflict(room->pipes[i], env, room->weight, room);
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
}
