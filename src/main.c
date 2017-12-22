/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourmea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:13:57 by pbourmea          #+#    #+#             */
/*   Updated: 2017/12/22 20:13:59 by pbourmea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cookielem_in.h"
#include <stdio.h>

static void	put_ants(t_env *env, t_room *pathroom)
{
	t_room	*cur;

	cur = pathroom;
	while (cur->prev != env->start)
	{
		if (cur->prev->ant)
		{
			cur->ant = cur->prev->ant;
			ft_printf("L%d-%s ", cur->ant, cur->name);
		}
		cur = cur->prev;
	}
	if (env->antleft)
	{
		cur->ant = env->nb_ants - env->antleft;
		ft_printf("L%d-%s ", cur->ant, cur->name);
		env->antleft--;
	}
}

void		out_pout(t_map *map/*, int v*/)
{
	unsigned long	lem_out;

	lem_out = 0;
	while ((int)lem_out < map->ant)
	{
		if (map->path->ant)
		{
			ft_printf("L%d-%s ", env->paths[0]->room->ant, env->paths[0]->room->name);
			lem_out++;
		}
		put_ants(env, env->paths[0]->room);
		ft_putchar('\n');
		//v = visu();
	}
}


void	ft_error(unsigned long motif)
{
	if (motif == 1)
		ft_putendl(ERR_ALLOC);
	else if (motif == 2)
		ft_putendl("Error");
	else if (motif == 3)
		ft_putendl("error format input\n");
	exit(-1);
}

int		main(void)
{
	t_map map;

	parser(&map);
	if (find_shortest(&map))
		out_pout(&map/*, 0*/);
	else
		ft_error(2);
	return (0);
}
