/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_step.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:24:50 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/20 19:13:51 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"
#include <limits.h>

static void		create_base_step(SDL_Renderer *render, int frame, t_visu *venv)
{
	boxRGBA(render, venv->screen.x - (frame * 16), 0, venv->screen.x, \
	venv->screen.y, 0, 0, 0, 160);
	boxRGBA(render, venv->screen.x - (frame * 16), \
	venv->step_select.y, venv->screen.x, \
	venv->step_select.y + venv->step_select.h, 150, 0, 0, 60);
	venv->step_size.x = venv->screen.x - ((frame * 16) - 30);
	venv->step_size.w = venv->screen.x / 4;
}

int				get_step(SDL_Renderer *render, int *step, t_visu *venv)
{
	static int	frame = 0;

	if (*step == 4 && frame > 0)
		frame--;
	else if (*step == 2 && frame < ((venv->screen.x / 4 + 30) / 16))
		frame++;
	else if (!venv->kb_state[SDL_SCANCODE_S] && *step == 1)
		*step = 2;
	else if (venv->kb_state[SDL_SCANCODE_S] && *step == 2)
		*step = 3;
	else if (!venv->kb_state[SDL_SCANCODE_S] && *step == 3)
		*step = 4;
	if (*step == 4 && frame == 0)
	{
		*step = 0;
		venv->step_focus.x = 0;
	}
	move_step(venv);
	if (*step == 2 || *step == 3)
		if (display_ants(render, venv))
			return (1);
	create_base_step(render, frame, venv);
	return (SDL_RenderCopy(render, venv->step, &venv->step_focus, \
	&venv->step_size));
}
