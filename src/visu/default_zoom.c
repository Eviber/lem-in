/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_zoom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:39:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/08 12:59:20 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static void		get_min_max(t_room **rooms, t_visu *venv)
{
	int		i;

	i = -1;
	venv->max.x = 0;
	venv->max.y = 0;
	venv->origin.x = venv->screen.x / 2;
	venv->origin.y = venv->screen.y / 2;
	while (rooms && rooms[++i])
	{
		if ((rooms[i])->pos.x > venv->max.x)
			venv->max.x = (rooms[i])->pos.x;
		if ((rooms[i])->pos.y > venv->max.y)
			venv->max.y = (rooms[i])->pos.y;
	}
	i = -1;
	venv->min = venv->max;
	while (rooms && rooms[++i])
	{
		if ((rooms[i])->pos.x < venv->min.x)
			venv->min.x = (rooms[i])->pos.x;
		if ((rooms[i])->pos.y < venv->min.y)
			venv->min.y = (rooms[i])->pos.y;
	}
}

static void		get_first_offset(int zoommod, t_visu *venv)
{
	venv->morigin.x = zoommod == DIV ? (((venv->max.x / venv->zoom) - \
	(venv->min.x / venv->zoom)) / 2) + (venv->min.x / venv->zoom) : \
	(((venv->max.x * venv->zoom) - (venv->min.x * venv->zoom)) / 2) + \
	(venv->min.x * venv->zoom);
	venv->morigin.y = zoommod == DIV ? (((venv->max.y / venv->zoom) - \
	(venv->min.y / venv->zoom)) / 2) + (venv->min.y / venv->zoom) : \
	(((venv->max.y * venv->zoom) - (venv->min.y * venv->zoom)) / 2) + \
	(venv->min.y * venv->zoom);
	venv->offset.x = venv->origin.x - venv->morigin.x;
	venv->offset.y = venv->origin.y - venv->morigin.y;
}

static void		apply_zoom(t_room **rooms, int zoommod, t_visu *venv)
{
	int		i;

	i = -1;
	venv->nb_rooms = 0;
	while (rooms[venv->nb_rooms])
		venv->nb_rooms++;
	if ((venv->pos = (t_pos*)malloc(sizeof(t_pos) * venv->nb_rooms)))
		while (rooms && rooms[++i])
		{
			rooms[i]->pos.x = (zoommod == DIV ? \
			rooms[i]->pos.x / venv->zoom + venv->offset.x : \
			rooms[i]->pos.x * venv->zoom + venv->offset.x) / 30;
			rooms[i]->pos.y = (zoommod == DIV ? \
			rooms[i]->pos.y / venv->zoom + venv->offset.y : \
			rooms[i]->pos.y * venv->zoom + venv->offset.y) / 30;
			venv->pos[i] = rooms[i]->pos;
		}
	venv->zoom = 30;
	venv->offset.x = 0;
	venv->offset.y = 0;
}

void			get_default_zoom(t_room **rooms, t_visu *venv)
{
	int		zoommod;

	get_min_max(rooms, venv);
	venv->zoom = 1;
	if ((venv->max.x - venv->min.x) > (venv->screen.x - 200) || \
	(venv->max.y - venv->min.y) > (venv->screen.y - 200))
		zoommod = DIV;
	else if ((venv->max.x - venv->min.x) <= (venv->screen.x - 200) || \
	(venv->max.y - venv->min.y) < (venv->screen.y - 200))
		zoommod = MULT;
	while (((venv->max.x / venv->zoom) - (venv->min.x / venv->zoom)) > \
	(venv->screen.x - 200) || ((venv->max.y / venv->zoom) - \
	(venv->min.y / venv->zoom)) > (venv->screen.y - 200))
		venv->zoom++;
	while (((venv->max.x * (venv->zoom + 1)) - (venv->min.x * \
	(venv->zoom + 1))) < (venv->screen.x - 200) && ((venv->max.y * \
	(venv->zoom + 1)) - (venv->min.y * (venv->zoom + 1))) < \
	(venv->screen.y - 200))
		venv->zoom++;
	get_first_offset(zoommod, venv);
	apply_zoom(rooms, zoommod, venv);
}
