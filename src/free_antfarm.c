/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_antfarm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:42:18 by sbrochar          #+#    #+#             */
/*   Updated: 2018/01/18 22:06:40 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
#include <eparser.h>

void				free_paths(t_path **paths)
{
	size_t			i;

	i = 0;
	while (paths && paths[i])
	{
		ft_memdel((void **)&(paths[i]));
		i++;
	}
	ft_memdel((void **)&paths);
}

void				free_rooms(t_room **rooms)
{
	size_t			i;

	i = 0;
	while (rooms && rooms[i])
	{
		ft_memdel((void **)&(rooms[i]->pipes));
		ft_strdel(&rooms[i]->name);
		ft_memdel((void **)&rooms[i]);
		i++;
	}
	ft_memdel((void **)&rooms);
}

void				free_antfarm(t_env *antfarm)
{
	antfarm->start = NULL;
	antfarm->end = NULL;
	if (antfarm->rooms)
		free_rooms(antfarm->rooms);
	if (antfarm->paths)
		free_paths(antfarm->paths);
}
