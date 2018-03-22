/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_conflict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:31:50 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/22 11:15:26 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include "visu.h"

void			save_conflict(t_room *origin, t_room *locked_room, t_env *env)
{
	env->conflit->old_room = locked_room;
	env->conflit->old_redirect = locked_room->prev;
	env->conflit->next = ft_memalloc(sizeof(t_conflict));
	env->conflit->state = env->conflict;
	env->conflit->to_redirect = origin;
	env->conflit->id = origin->locked;
	env->conflit->next->prev = env->conflit;
	env->conflit = env->conflit->next;
}

void			check_outflow(t_env *env, t_room *room, long output_weight)
{
	t_room	**pipes;
	int		i;

	i = 0;
	pipes = room->pipes;
	while (pipes[i])
	{
		if (pipes[i]->locked == 0 && pipes[i] != env->start)
		{
			pipes[i]->locked = env->conflict;
			if (pipes[i]->weight > output_weight || !pipes[i]->weight)
			{
				pipes[i]->weight_diff = room->weight_diff;
				pipes[i]->weight = output_weight;
				pipes[i]->prev = room;
			}
		}
		if (env->v)
			env->v = visu(room, pipes[i]);
		i++;
	}
}

void			conflict(t_room *locked_room, t_env *env,
						long depth, t_room *origin)
{
	long	output_weight;
	t_room	*cur;

	output_weight = depth + 1;
	cur = locked_room->prev;
	++env->conflict;
	while (cur->prev && !cur->next->dead)
	{
		cur->weight_diff = output_weight - depth - 2;
		cur->locked = env->conflict;
		check_outflow(env, cur, output_weight);
		output_weight--;
		cur = cur->prev;
	}
	env->depth = output_weight + 1;
	locked_room->dead = 1;
	save_conflict(origin, locked_room, env);
}
