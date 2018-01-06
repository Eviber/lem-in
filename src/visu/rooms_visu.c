/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 18:58:58 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/06 22:11:43 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

void	get_rooms_visu(SDL_Renderer *render, t_room **rooms, t_visu *venv)
{
	int		i;
	t_pos	new;

	i = -1;
	while (rooms && rooms[++i])
	{
		new.x = venv->zoommod == DIV ? \
		((rooms[i]->pos.x / venv->zoom) + venv->offset.x) : \
		((rooms[i]->pos.x * venv->zoom) + venv->offset.x);
		new.y = venv->zoommod == DIV ? \
		((rooms[i]->pos.y / venv->zoom) + venv->offset.y) : \
		((rooms[i]->pos.y * venv->zoom) + venv->offset.y);
		filledCircleRGBA(render, new.x, new.y, 50, 0, 0, 0, 255);
		filledCircleRGBA(render, new.x, new.y, 40, 47, 27, 12, 255);
		aacircleRGBA(render, new.x, new.y, 50, 0, 0, 0, 255);
		aacircleRGBA(render, new.x, new.y, 40, 47, 27, 12, 255);
	}
}
