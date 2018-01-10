/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:42:05 by ygaude            #+#    #+#             */
/*   Updated: 2018/01/10 02:48:09 by ygaude           ###   ########.fr       */
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
		if (!room->pipes[i]->weight && room->pipes[i] != env->start)
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

int				find_shortest(t_env *env)
{
	int		depth;

	depth = 1;
	env->paths = (t_path **)ft_memalloc(sizeof(t_path *));
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
