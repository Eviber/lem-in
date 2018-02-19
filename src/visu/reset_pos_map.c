/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_pos_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:21:21 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/29 14:33:04 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

void	reset_pos_map(t_visu *venv)
{
	static Uint32	ticks = 0;
	Uint32			tmp;

	tmp = SDL_GetTicks();
	if (tmp > ticks + 120)
	{
		venv->zoom = 30;
		venv->offset.x = 0;
		venv->offset.y = 0;
		ticks = tmp;
	}
}
