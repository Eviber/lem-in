/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:59:46 by sbrochar          #+#    #+#             */
/*   Updated: 2018/03/21 21:50:31 by ygaude           ###   ########.fr       */
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

int					main(int argc, char **argv)
{
	t_env			antfarm;

	antfarm = init_antfarm();
	antfarm.v = (argc == 2 && ft_strequ(argv[1], "-v"));
	if (!parse_antfarm(&antfarm))
	{
		ft_printf("ERROR\n");
		antfarm.v = 0;
	}
	else
	{
		ft_printf("%s\n", antfarm.to_print);
		if (antfarm.v && !visu_init(&antfarm))
		{
			ft_putstr_fd("Visualizer failed.\n", 2);
			antfarm.v = 0;
		}
		if (antfarm.start != antfarm.end && solve(&antfarm))
			output(&antfarm);
		else
			ft_printf("ERROR\n");
	}
	free_antfarm(&antfarm);
	return (0);
}
