/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 14:22:51 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/07 16:49:19 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static void		draw_pipe(SDL_Renderer *render, t_room *rooma, t_room *roomb, \
t_visu *venv)
{
	t_pos	posa;
	t_pos	posb;

	posa.x = /*venv->zoommod == DIV ? \
	(((rooma->pos.x / venv->zoom) + venv->offset.x)) : \*/
	(((rooma->pos.x * venv->zoom) + venv->offset.x));
	posa.y = /*venv->zoommod == DIV ? \
	(((rooma->pos.y / venv->zoom) + venv->offset.y)) : \*/
	(((rooma->pos.y * venv->zoom) + venv->offset.y));
	posb.x = /*venv->zoommod == DIV ? \
	(((roomb->pos.x / venv->zoom) + venv->offset.x)) : \*/
	(((roomb->pos.x * venv->zoom) + venv->offset.x));
	posb.y = /*venv->zoommod == DIV ? \
	(((roomb->pos.y / venv->zoom) + venv->offset.y)) : \*/
	(((roomb->pos.y * venv->zoom) + venv->offset.y));
	ft_printf("############\nScreen X = %d\nScreen Y = %d\nOrigin X = %d\nOrigin Y = %d\nZoom = %d\nOffset X = %d\nOffset Y = %d\nX1 = %d\nY1 = %d\nX2 = %d\nY2 = %d\n############\n", venv->screen.x, venv->screen.y, venv->origin.x, venv->origin.y, venv->zoom, venv->offset.x, venv->offset.y, posa.x, posa.y, posb.x, posb.y);
	thickLineRGBA(render, posa.x, posa.y, posb.x, posb.y, 20, 0, 0, 0, 180);
}

static int		check_double_pipe(t_room **rooms, t_room *current, int i)
{
	while (--i >= 0)
		if (rooms[i] == current)
			return (1);
	return (0);
}

void			get_pipes_visu(SDL_Renderer *render, t_room **rooms, t_visu *venv)
{
	int		i;
	int		j;

	i = -1;
/*	venv->offset.x -= ((venv->origin.x / venv->bzoom.x) * \
	(venv->bzoom.x + venv->zoom.x)) - venv->origin.x;
	venv->offset.y -= ((venv->origin.y / venv->bzoom.y) * \
	(venv->bzoom.y + venv->zoom.y)) - venv->origin.y;*/
	while (rooms && rooms[++i])
	{
		j = -1;
		while (rooms[i]->pipes && rooms[i]->pipes[++j])
		{
			if (!check_double_pipe(rooms, rooms[i]->pipes[j], i))
				draw_pipe(render, rooms[i], rooms[i]->pipes[j], venv);
		}
	}
}
