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
/*
static void	clean_conflict(t_env *env)
{
	printf("Nice\n");
	while (env->conflit->prev)
	{
		env->conflit = env->conflit->prev;
		ft_memdel(env->conflit->next);
	}
	//ft_memdel(env->conflit);
	printf("Nice\n");
}
*/
static int	search_conf(int set, int new_dp, t_env *env)
{
	t_conflit *tmp;
 	unsigned long mean_len;
	long conflit;

	tmp = env->conflit;
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
	tmp = env->conflit;
	if (mean_len / (env->nb_path + 1) < env->mean_len / env->nb_path)
	{
		set = env->conflict - 1;
		while(set)
		{
			while (set != tmp->state)
				tmp = tmp->prev;
			tmp->old_room->prev = tmp->miss_direction;
			set = tmp->state - 1;
		}
		//clean_conflict(env);
		return (TRUE);
	}
	//clean_conflict(env);
	return (FALSE);
}

int			save_info(int set, int new_dp, t_room *room, t_env *env)
{
	if (set == -2)
	{
		if (!env->conflit)
			env->conflit = memalloc_exit(sizeof(t_conflit));
		env->conflit->new_len = new_dp;
		env->conflit->old_room = room;
		env->conflit->next = memalloc_exit(sizeof(t_conflit));
		env->conflit->next->prev = env->conflit;
		env->conflit->state = env->conflict - 1;
		env->conflit = env->conflit->next;
	}
	else if (set == -1)
		env->conflit->prev->miss_direction = room;
	else if (set == 0)
		env->conflit->old_len = new_dp;
	else if (set > 0)
	{
		return (search_conf(--set, new_dp, env));
	}
	return (FALSE);
}

void		lock_path(t_env *env)
{
	t_path	*tmp;
	t_room	*room;
	int		len;

	env->nb_path = 0;
	env->mean_len = env->nb_ants;
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
