/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:32:52 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/21 21:33:19 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemin.h"
#include "visu.h"

static void		lock_path(t_env *env, t_path *path)
{
	t_room				*room;
	int					len;

	room = path->room;
	len = 0;
	room->next = env->end;
	while (room && room->prev && ++len)
	{
		room->prev->next = room;
		room->locked = -1;
		room = room->prev;
	}
	path->length = len;
	env->mean_len += len;
}

void			lock(t_env *env)
{
	int					i;

	i = 0;
	env->nb_path = 0;
	env->mean_len = env->nb_ants;
	while (env->paths[i] && env->paths[i]->room)
	{
		lock_path(env, env->paths[i++]);
		env->nb_path++;
	}
}
