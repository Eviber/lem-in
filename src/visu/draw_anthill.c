/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:22:51 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/29 16:46:30 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static int		draw_pipes(SDL_Renderer *render, int i, int j, t_visu *venv)
{
	return (thickLineRGBA(render, venv->pos[i].x, venv->pos[i].y, \
	venv->pos[j].x, venv->pos[j].y, 20, 0, 0, 0, 180));
}

static int		draw_rooms(SDL_Renderer *render, t_pos pos)
{
	if (filledCircleRGBA(render, pos.x, pos.y, 50, 0, 0, 0, 255))
		return (1);
	if (filledCircleRGBA(render, pos.x, pos.y, 40, 47, 27, 12, 255))
		return (1);
	if (aacircleRGBA(render, pos.x, pos.y, 50, 0, 0, 0, 255))
		return (1);
	if (aacircleRGBA(render, pos.x, pos.y, 40, 47, 27, 12, 255))
		return (1);
	return (0);
}

static int		check_double_pipe(t_room **rooms, t_room *current, int i)
{
	while (--i >= 0)
		if (rooms[i] == current)
			return (1);
	return (0);
}

int				draw_anthill(SDL_Renderer *render, t_room **rooms, t_visu *venv)
{
	int		i;
	int		j;

	i = -1;
	while (rooms && rooms[++i])
	{
		venv->pos[i].x = rooms[i]->pos.x * venv->zoom + venv->offset.x;
		venv->pos[i].y = rooms[i]->pos.y * venv->zoom + venv->offset.y;
	}
	i = -1;
	while (rooms && rooms[++i])
	{
		j = -1;
		while (rooms[i]->pipes && rooms[i]->pipes[++j])
			if (!check_double_pipe(rooms, rooms[i]->pipes[j], i))
				if (draw_pipes(render, i, \
				get_room_index(rooms, rooms[i]->pipes[j]), venv))
					return (1);
	}
	i = -1;
	while (rooms && rooms[++i])
		if (draw_rooms(render, venv->pos[i]))
			return (1);
	return (0);
}
