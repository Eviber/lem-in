/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:28:07 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/21 21:46:07 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include "solver.h"
#include "visu.h"

static void		set_pipe(t_env *env, t_room *room, t_room *parent)
{
	if (!room->weight && room != env->start
			&& (room->locked != 1 || parent == env->start))
	{
		room->weight_diff = parent->weight_diff;
		room->weight = parent->weight + 1;
		room->prev = parent;
		room->locked = parent->locked;
	}
}

static int		fill_weight(t_env *env, t_room *r)
{
	int					i;

	i = 0;
	while (r->pipes && r->pipes[i])
	{
		if (r->pipes[i] == env->end && (r->locked == 0 || check_conf(r, env)))
			return (TRUE);
		set_pipe(env, r->pipes[i], r);
		if (r != env->start && r->pipes[i]->locked == 1 &&
				(!r->pipes[i]->dead && r->locked != 1))
		{
			conflict(r->pipes[i], env, r->weight, r);
			return (FALSE);
		}
		if (env->v)
			env->v = visu(r, r->pipes[i]);
		i++;
	}
	return (FALSE);
}

static t_room	*try_path(t_env *env, int depth)
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

int				find_shortest(t_env *env, int f_iter)
{
	t_room				*tmp;
	static t_room		*f_room = NULL;

	env->depth = 1;
	while (env->depth <= env->nb_rooms - 1)
	{
		if ((tmp = try_path(env, env->depth++)))
		{
			if (tmp != f_room && ispathworth(env, tmp->weight))
			{
				if (!f_room)
					f_room = tmp;
				if (!env->paths[f_iter]->room)
					env->paths[f_iter]->room = tmp;
				return (TRUE);
			}
			else
				return (FALSE);
		}
	}
	return (FALSE);
}
