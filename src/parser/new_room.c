/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:08:44 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/11 21:08:58 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

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
	if (!(new[i] = (t_room*)ft_memalloc(sizeof(t_room))))
		lem_in_error(DEFAULT, 'q', env);
	new[i + 1] = NULL;
	ft_memdel((void**)&(env->rooms));
	env->rooms = new;
	return ((env->rooms)[i]);
}

t_room			*new_room(char *name, int x, int y, t_env *env)
{
	t_room	*new;

	if (search_room(name, env->rooms))
	{
		ft_dprintf(2, "lem-in: room \"%s\" already exist\n", name);
		exit(-1);
	}
	new = roomalloc(env);
	env->nb_rooms++;
	new->pipes = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->name = name;
	new->pos.x = x;
	new->pos.y = y;
	new->ant = 0;
	new->weight = 0;
	new->dead = 0;
	return (new);
}
