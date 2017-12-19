/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:12:14 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/19 16:44:14 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
#include <eparser.h>

static int			check_errors(char **tab)
{
	int				i;

	i = 0;
	if (tab && tab[0] && tab[1] && tab[2] && !tab[3])
	{
		if (tab[0][0] == 'L')
			return (FALSE);
		while ((tab[1])[i])
		{
			if (!ft_isdigit((tab[1])[i]))
				return (FALSE);
			i++;
		}
		i = 0;
		while ((tab[2])[i])
		{
			if (!ft_isdigit((tab[2])[i]))
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

static t_room		*init_room(char **tab)
{
	t_room			*ret;

	ret = (t_room *)ft_memalloc(sizeof(t_room));
	if (ret)
	{
		ret->pipes = NULL;
		ret->next = NULL;
		ret->prev = NULL;
		ret->name = ft_strdup(tab[0]);
		if (!(ret->name))
			return (NULL);
		ret->pos.x = ft_atoi(tab[1]);
		ret->pos.y = ft_atoi(tab[2]);
		ret->ant = 0;
		ret->weight = 0;
		ret->dead = 0;
		return (ret);
	}
	return (NULL);
}

static t_room		**add_room(t_room **rooms, int nb_rooms)
{
	t_room			**ret;
	size_t			old_size;
	size_t			new_size;

	old_size = sizeof(t_room *) * nb_rooms;
	new_size = sizeof(t_room *) + old_size;
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

static void			create_room(int *start, int *end, t_env *antfarm, char **tab)
{
	t_room			*room;
	static size_t	nb_rooms = 0;

	room = init_room(tab);
	if (room)
	{
		if (*start)
		{
			*start = FALSE;
			antfarm->start = room;
		}
		if (*end)
		{
			*end = FALSE;
			antfarm->end = room;
		}
		nb_rooms++;
		antfarm->rooms = (t_room **)add_room(antfarm->rooms, nb_rooms);
		(antfarm->rooms)[nb_rooms - 1] = room;
	}
}

int					parse_room(int *start, int *end, t_env *antfarm, char *line)
{
	char			**tab;
	char			*tmp;

	tmp = ft_strtrimall(line);
	tab = ft_strsplit(tmp, ' ');
	ft_strdel(&tmp);
	if (!check_errors(tab))
	{
		free_tab(&tab);
		return (FALSE);
	}
	create_room(start, end, antfarm, tab);
	free_tab(&tab);
	return (TRUE);
}
