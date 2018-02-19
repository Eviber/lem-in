/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:24:50 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/06 16:27:12 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"
#include <limits.h>

static void		event_move(t_visu *venv)
{
	if (venv->kb_state[SDL_SCANCODE_UP] && venv->offset.y > \
	-(venv->screen.y * ZOOM_MAX))
		venv->offset.y -= 8;
	if (venv->kb_state[SDL_SCANCODE_DOWN] && venv->offset.y < \
	venv->screen.y * ZOOM_MAX)
		venv->offset.y += 8;
	if (venv->kb_state[SDL_SCANCODE_LEFT] && venv->offset.x > \
	-(venv->screen.x * ZOOM_MAX))
		venv->offset.x -= 16;
	if (venv->kb_state[SDL_SCANCODE_RIGHT] && venv->offset.x < \
	venv->screen.x * ZOOM_MAX)
		venv->offset.x += 16;
}

static void		event_zoom(t_visu *venv)
{
	if (venv->kb_state[SDL_SCANCODE_KP_MINUS] && venv->zoom > 20)
	{
		venv->offset.x = venv->origin.x + (venv->offset.x - venv->origin.x) * \
		(venv->zoom - 1) / venv->zoom;
		venv->offset.y = venv->origin.y + (venv->offset.y - venv->origin.y) * \
		(venv->zoom - 1) / venv->zoom;
		venv->zoom--;
	}
	if (venv->kb_state[SDL_SCANCODE_KP_PLUS] && venv->zoom < ZOOM_MAX)
	{
		venv->offset.x = venv->origin.x + (venv->offset.x - venv->origin.x) * \
		(venv->zoom + 1) / venv->zoom;
		venv->offset.y = venv->origin.y + (venv->offset.y - venv->origin.y) * \
		(venv->zoom + 1) / venv->zoom;
		venv->zoom++;
	}
}

static int		get_step(SDL_Renderer *render, int *step, t_visu *venv)
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
	boxRGBA(render, venv->screen.x - (frame * 16), 0, venv->screen.x, \
	venv->screen.y, 0, 0, 0, 160);
	boxRGBA(render, venv->screen.x - (frame * 16), \
	venv->step_select.y, venv->screen.x, \
	venv->step_select.y + venv->step_select.h, 150, 0, 0, 60);
	venv->step_size.x = venv->screen.x - ((frame * 16) - 30);
	venv->step_size.w = venv->screen.x / 4;
	return (SDL_RenderCopy(render, venv->step, &venv->step_focus, \
	&venv->step_size));
}

static int		get_help(SDL_Renderer *render, int *help, t_visu *venv)
{
	static int		frame = 0;
	SDL_Rect		pos;

	if (*help == 4 && frame > 0)
		frame--;
	else if (*help == 2 && frame < 389 / 16)
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
	pos.x = (frame * 16) - 389;
	pos.y = 0;
	pos.w = 389;
	pos.h = 400;
	return (SDL_RenderCopy(render, venv->help, NULL, &pos));
}

int				event_manager(SDL_Renderer *render, t_visu *venv)
{
	int			ret;
	static int	help = 0;
	static int	step = 0;
	static int	rooms = 0;

	ret = 0;
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
		ret += get_rooms_name(render, &rooms, venv);
	if (step)
		ret += get_step(render, &step, venv);
	if (help)
		ret += get_help(render, &help, venv);
	if (venv->kb_state[SDL_SCANCODE_SPACE])
		reset_pos_map(venv);
	return (ret);
}
