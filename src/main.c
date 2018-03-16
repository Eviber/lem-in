/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:59:46 by sbrochar          #+#    #+#             */
/*   Updated: 2018/02/08 15:34:41 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "eparser.h"
#include "solver.h"
#include "visu.h"

t_room				**add_room(t_room **rooms, int nb_rooms)
{
	t_room			**ret;
	size_t			old_size;
	size_t			new_size;

	old_size = sizeof(t_room *) * nb_rooms;
	new_size = sizeof(t_room *) * (nb_rooms + 2);
	if (!rooms)
	{
		if ((ret = (t_room **)ft_memalloc(new_size)))
			return (ret);
	}
	else
	{
		ret = (t_room **)ft_memalloc(new_size);
		if (ret)
		{
			ft_memcpy(ret, rooms, old_size);
			ft_memdel((void **)&rooms);
			return (ret);
		}
	}
	return (NULL);
}

t_room				*find_room(t_env *antfarm, char *name)
{
	t_room			**rooms;

	rooms = antfarm->rooms;
	while (name && rooms && *rooms)
	{
		if ((*rooms)->name && !ft_strcmp(name, (*rooms)->name))
			return (*rooms);
		rooms++;
	}
	return (NULL);
}

static t_env		init_antfarm(void)
{
	t_env			ret;

	ft_bzero(&ret, sizeof(t_env));
	ret.conflit = ft_memalloc(sizeof(t_conflict));
	return (ret);
}

/*static void		debug_room(t_room room)
{
	ft_printf("%s : pos={%d;%d} ; prev=%p ; next=%p ; ant=%ld ; weight=%d ; dead=%d ; pipes=%p \n", room.name, room.pos.x, room.pos.y, room.prev, room.next, room.ant, room.weight, room.dead, room.pipes);
}

static void			debug_pipes(t_room **pipes)
{
	int				i;

	i = 0;
	if (pipes)
	{
		ft_printf("tab of pipes: %p\n", pipes);
		while (pipes[i])
		{
			ft_printf("%s : pos={%d;%d} ; prev=%p ; next=%p ; ant=%ld ; weight=%d ; dead=%d ; pipes=%p \n", pipes[i]->name, pipes[i]->pos.x, pipes[i]->pos.y, pipes[i]->prev, pipes[i]->next, pipes[i]->ant, pipes[i]->weight, pipes[i]->dead, pipes[i]->pipes);
			i++;
		}
	}
}

void				debug_colony(t_env colony)
{
	int				i;

	i = 0;
	ft_printf("start=%s\nend=%s\npaths=%p\nrooms=%p\nnb_ants=%ld\nantleft=%ld\n\n", colony.start->name, colony.end->name, colony.paths, colony.rooms, colony.nb_ants, colony.antleft);
	while (colony.rooms && (colony.rooms)[i])
	{
		debug_room(*(colony.rooms[i]));
		i++;
	}
		ft_printf("tubes of first room:\n");
		t_room *first_room = *(colony.rooms);
		debug_pipes(first_room->pipes);
}*/

int					main(int argc, char **argv)
{
	t_env			antfarm;
	int				v;

	v = (argc == 2 && ft_strequ(argv[1], "-v"));
	antfarm = init_antfarm();
	if (!parse_antfarm(&antfarm))
	{
		ft_printf("ERROR\n");
		v = 0;
	}
	else
	{
		ft_printf("%s\n", antfarm.to_print);
		if (v && !visu_init(&antfarm))
		{
			ft_putstr_fd("Visualizer failed.\n", 2);
			v = 0;
		}
//		debug_colony(antfarm);
		if (antfarm.start != antfarm.end && solve(&antfarm, &v))
			output(&antfarm, v);
		else
			ft_printf("ERROR\n");
	}
	free_antfarm(&antfarm);
	return (0);
}
