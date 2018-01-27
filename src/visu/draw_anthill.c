/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_anthill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:22:51 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/27 14:44:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static void		draw_pipes(SDL_Renderer *render, int i, int j, t_visu *venv)
{
//	ft_printf("############\nScreen X = %d\nScreen Y = %d\nOrigin X = %d\nOrigin Y = %d\nZoom = %d\nOffset X = %d\nOffset Y = %d\nX1 = %d\nY1 = %d\nX2 = %d\nY2 = %d\n############\n", venv->screen.x, venv->screen.y, venv->origin.x, venv->origin.y, venv->zoom, venv->offset.x, venv->offset.y, venv->pos[i].x, venv->pos[i].y, venv->pos[j].x, venv->pos[j].y);
	thickLineRGBA(render, venv->pos[i].x, venv->pos[i].y, venv->pos[j].x, \
	venv->pos[j].y, 20, 0, 0, 0, 180);
}

static void		draw_rooms(SDL_Renderer *render, t_pos pos)
{
	filledCircleRGBA(render, pos.x, pos.y, 50, 0, 0, 0, 255);
	filledCircleRGBA(render, pos.x, pos.y, 40, 47, 27, 12, 255);
	aacircleRGBA(render, pos.x, pos.y, 50, 0, 0, 0, 255);
	aacircleRGBA(render, pos.x, pos.y, 40, 47, 27, 12, 255);
}

static int		check_double_pipe(t_room **rooms, t_room *current, int i)
{
	while (--i >= 0)
		if (rooms[i] == current)
			return (1);
	return (0);
}

void			draw_anthill(SDL_Renderer *render, t_room **rooms, t_visu *venv)
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
		{
			if (!check_double_pipe(rooms, rooms[i]->pipes[j], i))
				draw_pipes(render, i, \
				get_room_index(rooms, rooms[i]->pipes[j]), venv);
		}
	}
	i = -1;
	while (rooms && rooms[++i])
		draw_rooms(render, venv->pos[i]);
}
