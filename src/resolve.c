/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourmea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 22:05:57 by pbourmea          #+#    #+#             */
/*   Updated: 2017/12/22 22:06:01 by pbourmea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cookielem_in.h"

static int		fill_weight(const t_map *map, t_room *room)
{
	room->tubes = room->a_tube;
	while (room->tubes->room)
	{
		if (room->tubes->room == map->end)
		{
			map->end->prev = room;
			return (TRUE);
		}
		if (!room->tubes->room->weight && room->tubes->room != map->start)
		{
			room->tubes->room->weight = room->weight + 1;
			room->tubes->room->prev = room;
		}
		room->tubes = room->tubes->next;
	}
	return (FALSE);
}

static t_room	*try_path(t_map *map, int depth)
{
	t_room	*cur;
	int		i;

	i = 0;
	cur = map->rooms;
	while (cur)
	{
		if (cur->weight == depth - 1 && (cur->weight || cur == map->start))
			if (fill_weight(map, cur))
				return (map->end);
		cur = cur->next;
	}
	return (NULL);
}

int				find_shortest(t_map *map)
{
	unsigned long		depth;

	depth = 0;
	map->path = ft_memalloc(sizeof(t_room *));
	while (++depth <= map->nb_rooms - 1)
		if ((map->path = try_path(map, depth)))
			return (TRUE);
	return (FALSE);
}
