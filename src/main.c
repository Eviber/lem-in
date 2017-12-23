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

static void	output_ant(int name_ant, char *name_room)
{
	write(1, "L", 1);
	ft_putnbr(name_ant);
	write(1, "-", 1);
	ft_putstr(name_room);
	write(1, " ", 1);
}

static void	put_ants(t_map *map)
{
	t_room	*cur;

	cur = map->end;
	while (cur->prev != map->start)
	{
		if (cur->prev->ant)
		{
			cur->ant = cur->prev->ant;
			cur->prev->ant = 0;
			output_ant(cur->ant, cur->name);
		}
		cur = cur->prev;
	}
	if (map->antleft)
	{
		cur->ant = map->ant - map->antleft + 1;
		output_ant(cur->ant, cur->name);
		map->antleft -= 1;
	}
}

void		out_pout(t_map *map)
{
	unsigned long	lem_out;

	lem_out = 1;
	ft_putchar('\n');
	while (lem_out < map->ant)
	{
		if (map->end->ant)
			lem_out++;
		put_ants(map);
		ft_putchar('\n');
		//v = visu();
	}
}

void		ft_error(unsigned long motif)
{
	if (motif == 1)
		ft_putendl(ERR_ALLOC);
	else if (motif == 2)
		ft_putendl("ERROR\n");
	else if (motif == 3)
		ft_putendl("error format input\n");
	exit(-1);
}

int			main(void)
{
	t_map *map;

	map = ft_memalloc(sizeof(t_map));
	parser(map);
	map->antleft = map->ant;
	if (find_shortest(map))
		out_pout(map);
	else
		ft_error(2);
	return (0);
}
