/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_step.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 21:04:11 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/20 19:05:59 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static void		horizontal_scrolling(t_visu *venv)
{
	t_pos	tmp;

	SDL_QueryTexture(venv->step, NULL, NULL, &tmp.x, &tmp.y);
	venv->step_focus.w = venv->screen.x / 4;
	venv->step_focus.h = venv->step_size.h;
	venv->step_focus.y = 0;
	if (venv->kb_state[SDL_SCANCODE_M] && venv->step_focus.x < tmp.x - \
	venv->step_focus.w)
		venv->step_focus.x += 4;
	else if (venv->kb_state[SDL_SCANCODE_N] && venv->step_focus.x > 0)
		venv->step_focus.x -= 4;
}

static void		move_up(t_visu *venv)
{
	(venv->i)--;
	if (venv->step_select.y > 25 && (venv->step_size.y + venv->step_size.h\
	>= venv->screen.y || venv->step_size.h < venv->screen.y))
		venv->step_select.y -= 50;
	else if (venv->step_size.y < 0)
		venv->step_size.y += 50;
}

static void		move_down(t_visu *venv)
{
	(venv->i)++;
	if (venv->step_select.y + venv->step_select.h + 50 <= venv->screen.y)
		venv->step_select.y += 50;
	else if (venv->step_size.y + venv->step_size.h >= venv->screen.y)
		venv->step_size.y -= 50;
}

void			move_step(t_visu *venv)
{
	Uint32			tmp;
	static Uint32	ticks = 0;

	tmp = SDL_GetTicks();
	if (venv->kb_state[SDL_SCANCODE_J] && venv->i > 0 && tmp > ticks + 120)
	{
		move_up(venv);
		ticks = SDL_GetTicks();
	}
	else if (venv->kb_state[SDL_SCANCODE_K] && \
	venv->step_list[venv->i + 1] && tmp > ticks + 120 && (venv->step_size.y +\
	venv->step_size.h >= venv->screen.y || venv->step_size.h < venv->screen.y))
	{
		move_down(venv);
		ticks = SDL_GetTicks();
	}
	horizontal_scrolling(venv);
}
