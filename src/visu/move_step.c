/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 21:04:11 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/27 14:10:40 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

void	move_step(t_visu *venv)
{
	Uint32			tmp;
	static Uint32	ticks = 0;

	tmp = SDL_GetTicks();
	if (venv->kb_state[SDL_SCANCODE_J] && venv->i > 0 && tmp > ticks + 120)
	{
		(venv->i)--;
		if (venv->step_select.y > 25)
			venv->step_select.y -= 50;
		else if (venv->step_size.y < 0)
			venv->step_size.y += 50;
		ticks = SDL_GetTicks();
	}
	else if (venv->kb_state[SDL_SCANCODE_K] && \
	venv->step_list[venv->i + 1] && tmp > ticks + 120)
	{
		(venv->i)++;
		if (venv->step_select.y + venv->step_select.h + 50 <= venv->screen.y)
			venv->step_select.y += 50;
		else if (venv->step_size.y + venv->step_size.h >= venv->screen.y)
			venv->step_size.y -= 50;
		ticks = SDL_GetTicks();
	}
}
