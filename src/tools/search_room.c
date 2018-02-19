/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:20:08 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/01 00:15:27 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

t_room	*search_room(char *name, t_room **room)
{
	int		i;

	i = 0;
	if (name && room)
	{
		while (room[i] && ft_strcmp(name, (room[i])->name))
			i++;
		return (room[i]);
	}
	else
		return (NULL);
}
