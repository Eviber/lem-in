/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:44:35 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/16 19:54:03 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

void	del_room_tab(t_room **room)
{
	int		i;

	i = 0;
	while (room && room[i])
	{
		ft_strdel(&((room[i])->name));
		ft_memdel((void**)&((room[i])->pipes));
		ft_memdel((void**)&(room[i]));
		i++;
	}
	ft_memdel((void**)&room);
}
