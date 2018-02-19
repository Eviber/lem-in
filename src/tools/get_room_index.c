/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 14:40:15 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/27 14:42:24 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

int		get_room_index(t_room **rooms, t_room *src)
{
	int		i;

	i = 0;
	while (rooms && rooms[i] && rooms[i] != src)
		i++;
	if (rooms[i])
		return (i);
	else
		return (-1);
}
