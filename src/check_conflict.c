/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_conflict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:29:29 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/22 11:17:48 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lemin.h"
#include "solver.h"
#include "visu.h"

int			ispathworth(t_env *env, int depth)
{
	int				i;
	int				total_len;
	unsigned int	meanlen;
	int				mod;
	int				ret;

	total_len = env->mean_len + depth;
	meanlen = total_len / (env->nb_path + 1);
	mod = total_len % (env->nb_path + 1);
	ret = env->nb_ants;
	i = -1;
	if (env->nb_path && env->mean_len / env->nb_path < meanlen)
		return (0);
	while (++i < env->nb_path)
	{
		ret -= meanlen - env->paths[i]->length + (mod > 0);
		mod--;
	}
	return (ret > 0);
}

static void	assume_conflict(int origlock, t_conflict *tmp)
{
	while (origlock)
	{
		while (origlock != tmp->state)
			tmp = tmp->prev;
		origlock = tmp->id;
		tmp->old_room->prev = tmp->to_redirect;
	}
}

static int	revert_conflict(int origlock, t_conflict *tmp)
{
	while (origlock)
	{
		while (origlock != tmp->state)
			tmp = tmp->prev;
		origlock = tmp->id;
		tmp->old_room->prev = tmp->old_redirect;
	}
	return (FALSE);
}

static void	calcul_path(t_env *env)
{
	t_room	*room;
	int		len;
	int		i;

	i = 0;
	env->mean_len = env->nb_ants;
	while (env->paths[i] && env->paths[i]->room)
	{
		room = env->paths[i]->room;
		len = 1;
		while (room && room->prev)
		{
			room = room->prev;
			len++;
		}
		env->paths[i]->length = len;
		env->mean_len += len;
		i++;
	}
}

int			check_conf(t_room *room, t_env *env)
{
	t_conflict	*oldconf;
	int			origlock;
	long		new_dp;

	origlock = room->locked;
	new_dp = room->weight + room->weight_diff;
	assume_conflict(origlock, env->conflit);
	calcul_path(env);
	oldconf = env->conflit;
	if (!ispathworth(env, new_dp + 1))
		return (revert_conflict(origlock, oldconf));
	return (TRUE);
}
