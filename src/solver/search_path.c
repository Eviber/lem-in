/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/12 13:45:07 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"
#include "parser_lem_in.h"
#include "solver.h"

void			conflit(t_room *r, t_env *env, long depth, t_room *r_conf)
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
		tmp->lock = env->conflict;
		tmp->weight = --tmp_dp;
		tmp = tmp->prev;
	}
	env->dp = tmp_dp - 1;
	depth = depth + 1 - r->weight + dp;
	r->dead = 1;
	save_info(-2, depth, r, env);
	save_info(-1, depth, r_conf, env);
	save_info(0, dp, r_conf, env);
}

static int		fill_weight(t_env *env, t_room *r)
{
	int		i;

	i = -1;
	while (r->pipes && r->pipes[++i])
	{
		if (r->pipes[i] == env->end)
		{
			if (r->lock == 0 || save_info(r->lock, r->weight - 1, NULL, env))
			{
				return (TRUE);
			}
		}
		if (!r->pipes[i]->weight && r->pipes[i] != env->start)
			if (r->pipes[i]->lock != 1 || r == env->start)
			{
				r->pipes[i]->weight = r->weight + 1;
				r->pipes[i]->prev = r;
				r->pipes[i]->lock = r->lock;
			}
		if (r != env->start && r->pipes[i]->lock == 1)
			if (!r->pipes[i]->dead && r->lock != 1)
			{
				conflit(r->pipes[i], env, r->weight, r);
				return (FALSE);
			}
	}
	return (FALSE);
}

t_room			*try_path(t_env *env, int depth)
{
	t_room	*cur;
	int		i;

	i = 0;

	while (env->rooms[i])
	{
		cur = env->rooms[i++];
		if (cur->lock != 1 && (cur->weight || cur == env->start))
			if (cur->weight == depth - 1)
				if (fill_weight(env, cur))
					return (cur);
	}
	return (NULL);
}

int				find_shortest(t_env *e)
{
	t_room			*tmp;
	static t_room	*f_room = NULL;

	e->dp = 1;
	while (e->dp <= e->nb_rooms)
	{
		if ((tmp = try_path(e, e->dp++)))
			if (tmp)
			{
				if (!f_room)
					f_room = tmp;
				if (!e->paths->room)
					e->paths->room = tmp;
				return (TRUE);
			}
	}
	return (FALSE);
}

void			get_path(t_env *env)
{
	t_room	*tmp;

	env->paths = (t_path *)memalloc_exit(sizeof(t_path));
	while (env->nb_path < env->nb_ants && find_shortest(env) )
	{
		env->conflict = 1;
		clean_conflict(env);
		tmp = env->paths->room;
		tmp->next = env->end;
		lock_path(env);
		reset_room(env);
		env->paths->next = (t_path *)memalloc_exit(sizeof(t_path ));
		env->paths->next->prev = env->paths;
		env->paths = env->paths->next;
	}
	if (!env->paths->room && env->paths->prev)
		env->paths = env->paths->prev;
	lock_path(env);

}
