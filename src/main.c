/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:59:46 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/19 16:44:41 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
#include <eparser.h>

static t_env			init_antfarm(void)
{
	t_env				ret;

	ret.start = NULL;
	ret.end = NULL;
	ret.paths = NULL;
	ret.rooms = NULL;
	ret.nb_ants = -1;
	ret.antleft = -1;
	return (ret);
}

static void				debug_room(t_room room)
{
	ft_printf("%s : pos={%d;%d} ; prev=%p ; next=%p ; ant=%ld ; weight=%d ; dead=%d ; pipes=%p \n", room.name, room.pos.x, room.pos.y, room.prev, room.next, room.ant, room.weight, room.dead, room.pipes);
}

static void				debug_colony(t_env colony)
{
	int		i;

	i = 0;
	ft_printf("start=%s\nend=%s\npaths=%p\nrooms=%p\nnb_ants=%ld\nantleft=%ld\n\n", colony.start->name, colony.end->name, colony.paths, colony.rooms, colony.nb_ants, colony.antleft);
	while (colony.rooms && (colony.rooms)[i])
	{
		debug_room(*(colony.rooms[i]));
		i++;
	}
}

int						main(void)
{
	t_env				antfarm;

	antfarm = init_antfarm();
	if (!parse_antfarm(&antfarm))
		ft_printf("ERROR\n");
	else
	{
		ft_printf("Okay!\n");
		debug_colony(antfarm);
//		solver(&antfarm);
//		output(&antfarm);
	}
	return (0);
}
