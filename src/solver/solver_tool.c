/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:09:08 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/12 13:45:32 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "solver.h"

#include <stdio.h>

static void	clean_conflict(t_conflit **conflit)
{
	while ((*conflit)->prev)
	{
		*conflit = (*conflit)->prev;
		ft_memdel((void**)&((*conflit)->next));
	}
	ft_memdel((void**)conflit);
}

static int	search_conf(t_conflit **conf, int set, int new_dp, t_env *env)
{
	t_conflit *tmp;
 	unsigned long mean_len;
	long conflit;

	tmp = *conf;
	conflit = env->conflict;
	mean_len = env->mean_len + new_dp;
	while(set)
	{
		printf("here = set = %d\n",set);
		while (set != tmp->state)
		{
			tmp = tmp->prev;
		}
		set = tmp->state - 1;
		mean_len = mean_len - tmp->old_len + tmp->new_len;
	}
	tmp = *conf;
	if (mean_len / env->nb_path < env->mean_len / env->nb_path)
	{
		set = env->conflict;
		while(set)
		{
			while (set != tmp->state)
				tmp = tmp->prev;
			tmp->old_room->prev = tmp->miss_direction;
			set = tmp->state;
		}
		clean_conflict(conf);
		return (TRUE);
	}
	clean_conflict(conf);
	return (FALSE);
}

int			save_info(int set, int new_dp, t_room *room, t_env *env)
{
	static t_conflit *conflict = NULL;

	if (set == -2)
	{
		if (!conflict)
			conflict = memalloc_exit(sizeof(t_conflit));
		conflict->new_len = new_dp;
		conflict->old_room = room;
		conflict->next = memalloc_exit(sizeof(t_conflit));
		conflict->next->prev = conflict;
		conflict->state = env->conflict - 1;
		ft_printf("new_len = %ld\nnew_len = %ld\nstate = %ld\nroom = %s\n", conflict->new_len, conflict->old_len, conflict->state, conflict->old_room->name);
		conflict = conflict->next;
	}
	else if (set == -1)
		conflict->prev->miss_direction = room;
	else if (set == 0)
		conflict->old_len = new_dp;
	else if (set > 0)
	{
		return (search_conf(&conflict, --set, new_dp, env));
	}
	return (FALSE);
}

void		lock_path(t_env *env)
{
	t_path	*tmp;
	t_room	*room;
	int		len;

	env->nb_path = 0;
	env->mean_len = 0;
	tmp = env->paths;
	while (tmp && tmp->room)
	{
		room = tmp->room;
		len = 1;
		room->next = env->end;
		while (room && room->prev)
		{
			room->prev->next = room;
			room->lock = -1;
			room = room->prev;
			len++;
		}
		env->nb_path++;
		tmp->length = len;
		env->mean_len += len;
		tmp = tmp->prev;
	}
}

void		reset_room(t_env *env)
{
	int i;

	i = -1;
	while (env->rooms[++i])
	{
		if (env->rooms[i]->lock != -1)
			env->rooms[i]->weight = 0;
		if (env->rooms[i]->lock != -1)
			env->rooms[i]->lock = 0;
		else
			env->rooms[i]->lock = 1;
		env->rooms[i]->dead = 0;
	}
}
