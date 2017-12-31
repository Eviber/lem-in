/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:08:44 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/30 14:41:26 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser_lem-in.h"

static t_room	*roomalloc(t_env *env)
{
	int		i;
	int		size;
	t_room	**new;

	i = 0;
	size = 0;
	while (env->rooms && (env->rooms)[size])
		size++;
	size++;
	if (!(new = (t_room**)malloc(sizeof(t_room*) * (size + 1))))
		lem_in_error(DEFAULT, 'q', env);
	while (env->rooms && (env->rooms)[i])
	{
		new[i] = (env->rooms)[i];
		i++;
	}
	if (!(new[i] = (t_room*)malloc(sizeof(t_room))))
		lem_in_error(DEFAULT, 'q', env);
	new[i + 1] = NULL;
	ft_memdel((void**)&(env->rooms));
	env->rooms = new;
	return ((env->rooms)[i]);
}

t_room			*new_room(char *name, int x,  int y, t_env *env)
{
	t_room	*new;

	new = roomalloc(env);
	new->pipes = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->name = name;
	new->pos.x = x;
	new->pos.y = y;
	new->ant = 0;
	new->weight = 0;
	new->dead = 0;
}
