/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:24:50 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/27 15:30:48 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"
#include <limits.h>

static void		event_move(t_visu *venv)
{
	if (venv->kb_state[SDL_SCANCODE_UP])
		venv->offset.y -= 2;
	if (venv->kb_state[SDL_SCANCODE_DOWN])
		venv->offset.y += 2;
	if (venv->kb_state[SDL_SCANCODE_LEFT])
		venv->offset.x -= 4;
	if (venv->kb_state[SDL_SCANCODE_RIGHT])
		venv->offset.x += 4;
}

static void		event_zoom(t_visu *venv)
{
	if (venv->kb_state[SDL_SCANCODE_KP_MINUS] && venv->zoom > 30)
	{
		venv->offset.x = venv->origin.x + (venv->offset.x - venv->origin.x) * \
		(venv->zoom - 1) / venv->zoom;
		venv->offset.y = venv->origin.y + (venv->offset.y - venv->origin.y) * \
		(venv->zoom - 1) / venv->zoom;
		venv->zoom--;
	}
	if (venv->kb_state[SDL_SCANCODE_KP_PLUS] && (venv->min.x * venv->zoom + venv->offset.x) > INT_MIN && (venv->min.y * venv->zoom + venv->offset.y) > INT_MIN && (venv->max.x * venv->zoom + venv->offset.x) < INT_MAX && (venv->max.y * venv->zoom + venv->offset.y) < INT_MAX)
	{
		venv->offset.x = venv->origin.x + (venv->offset.x - venv->origin.x) * \
		(venv->zoom + 1) / venv->zoom;
		venv->offset.y = venv->origin.y + (venv->offset.y - venv->origin.y) * \
		(venv->zoom + 1) / venv->zoom;
		venv->zoom++;
	}
}

static void		get_step(SDL_Renderer *render, int *step, t_visu *venv)
{
	static int	frame = 0;

	if (*step == 4 && frame > 0)
		frame--;
	else if (*step == 2 && frame < ((venv->step_size.w + 60) / 3))
		frame++;
	else if (!venv->kb_state[SDL_SCANCODE_S] && *step == 1)
		*step = 2;
	else if (venv->kb_state[SDL_SCANCODE_S] && *step == 2)
		*step = 3;
	else if (!venv->kb_state[SDL_SCANCODE_S] && *step == 3)
		*step = 4;
	move_step(venv);
	display_ants(render, venv);
	if (*step == 4 && frame == 0)
		*step = 0;
	boxRGBA(render, venv->screen.x - (frame * 3), 0, venv->screen.x, \
	venv->screen.y, 0, 0, 0, 160);
	boxRGBA(render, venv->screen.x - (frame * 3), \
	venv->step_select.y, venv->screen.x, \
	venv->step_select.y + venv->step_select.h, 150, 0, 0, 60);
	venv->step_size.x = venv->screen.x - ((frame * 3) - 30);
	SDL_RenderCopy(render, venv->step, NULL, &venv->step_size);
}

static void		get_help(SDL_Renderer *render, int *help, t_visu *venv)
{
	static int		frame = 0;
	SDL_Rect		pos;

	if (*help == 4 && frame > 0)
		frame--;
	else if (*help == 2 && frame < 210)
		frame++;
	else if (!venv->kb_state[SDL_SCANCODE_H] && \
	!venv->kb_state[SDL_SCANCODE_F1] && *help == 1)
		*help = 2;
	else if ((venv->kb_state[SDL_SCANCODE_H] || \
	venv->kb_state[SDL_SCANCODE_F1]) && *help == 2)
		*help = 3;
	else if (!venv->kb_state[SDL_SCANCODE_H] && \
	!venv->kb_state[SDL_SCANCODE_F1] && *help == 3)
		*help = 4;
	if (*help == 4 && frame == 0)
	*help = 0;
	pos.x = (frame * 3) - 630;
	pos.y = 0;
	pos.w = 630;
	pos.h = 400;
	SDL_RenderCopy(render, venv->help, NULL, &pos);
}

void			event_manager(SDL_Renderer *render, t_visu *venv)
{
	static int	help = 0;
	static int	step = 0;
	static int	rooms = 0;

	if (!render)
		return ;
	SDL_PumpEvents();
	event_move(venv);
	event_zoom(venv);
	if ((venv->kb_state[SDL_SCANCODE_H] || \
	venv->kb_state[SDL_SCANCODE_F1]) && !help)
		help = 1;
	if (venv->kb_state[SDL_SCANCODE_S] && !step)
		step = 1;
	if (venv->kb_state[SDL_SCANCODE_R] && !rooms)
		rooms = 1;
	if (rooms)
		get_rooms_name(render, &rooms, venv);
	if (step)
		get_step(render, &step, venv);
	if (help)
		get_help(render, &help, venv);
}
