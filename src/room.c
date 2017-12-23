/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourmea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:13:41 by pbourmea          #+#    #+#             */
/*   Updated: 2017/12/22 20:13:45 by pbourmea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cookielem_in.h"

void		connect_rooms(t_map *map)
{
	t_room *ptr1;
	t_room *ptr2;

	ptr1 = map->tmp[0];
	ptr2 = map->tmp[1];
	ptr1->tubes = ptr1->a_tube;
	ptr2->tubes = ptr2->a_tube;
	while (ptr1->tubes->room)
		ptr1->tubes = ptr1->tubes->next;
	while (ptr2->tubes->room)
		ptr2->tubes = ptr2->tubes->next;
	ptr1->tubes->room = ptr2;
	ptr2->tubes->room = ptr1;
	ptr1->tubes->next = (t_tube*)ft_memalloc(sizeof(t_tube));
	ptr2->tubes->next = (t_tube*)ft_memalloc(sizeof(t_tube));
}

static void	push_room(t_map *map, t_room *room)
{
	t_room *tmp;

	map->nb_rooms += 1;
	if (!map->rooms)
		map->rooms = room;
	else
	{
		tmp = map->rooms;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = room;
	}
}
/*
void	room_print(t_room *room)
{
	t_room *ptr;

	ptr = room;
	while (ptr)
	{
		ft_putendl(ptr->name);
		ptr->tubes = ptr->a_tube;
		while (ptr->tubes->room)
		{
			printf("%s - %s\n", ptr->name, ptr->tubes->room->name);
			ptr->tubes = ptr->tubes->next;
		}
		ptr = ptr->next;
	}
}*/

void		init_room(t_map *map, t_room *room, char **data, int p_status)
{
	room->name = ft_strdup(data[0]);
	room->x = ft_atoi(data[1]);
	room->y = ft_atoi(data[2]);
	room->next = NULL;
	room->tubes = ft_memalloc(sizeof(t_tube));
	room->a_tube = room->tubes;
	if (p_status == START)
		map->start = room;
	else if (p_status == END)
		map->end = room;
	push_room(map, room);
}
