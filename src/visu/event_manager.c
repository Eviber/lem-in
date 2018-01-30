/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:24:50 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/07 20:21:29 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"
#include <limits.h>

static void		event_move(const Uint8 *kb_state, t_visu *venv)
{
	if (kb_state[SDL_SCANCODE_UP])
		venv->offset.y -= 2;
	if (kb_state[SDL_SCANCODE_DOWN])
		venv->offset.y += 2;
	if (kb_state[SDL_SCANCODE_LEFT])
		venv->offset.x -= 4;
	if (kb_state[SDL_SCANCODE_RIGHT])
		venv->offset.x += 4;
}

static void		event_zoom(const Uint8 *kb_state, t_visu *venv)
{
	if (kb_state[SDL_SCANCODE_KP_MINUS] && venv->zoom > 30)
	{
		venv->offset.x = venv->origin.x + (venv->offset.x - venv->origin.x) * \
		(venv->zoom - 1) / venv->zoom;
		venv->offset.y = venv->origin.y + (venv->offset.y - venv->origin.y) * \
		(venv->zoom - 1) / venv->zoom;
		venv->zoom--;
	}
	if (kb_state[SDL_SCANCODE_KP_PLUS] && (venv->min.x * venv->zoom + venv->offset.x) > INT_MIN && (venv->min.y * venv->zoom + venv->offset.y) > INT_MIN && (venv->max.x * venv->zoom + venv->offset.x) < INT_MAX && (venv->max.y * venv->zoom + venv->offset.y) < INT_MAX)
	{
		venv->offset.x = venv->origin.x + (venv->offset.x - venv->origin.x) * \
		(venv->zoom + 1) / venv->zoom;
		venv->offset.y = venv->origin.y + (venv->offset.y - venv->origin.y) * \
		(venv->zoom + 1) / venv->zoom;
		venv->zoom++;
	}
}

static void		get_help(SDL_Renderer *render, const Uint8 *kb_state, int *help)
{
	static int	frame = 0;

	if (*help == 2 && frame > 0)
		frame--;
	else if (frame < 100)
		frame++;
	else if ((kb_state[SDL_SCANCODE_H] || kb_state[SDL_SCANCODE_F1]) && *help == 1)
		*help = 2;
	if (*help == 2 && frame == 0)
		*help = 0;
	boxRGBA(render, 0, 0, frame * 2, 300, 0, 0, 0, 150);
}

static void		get_slider(SDL_Renderer *render, int sstate, int *slider, t_pos screen)
{
	static int	frame = 0;

	if (*slider == 2 && frame > 0)
		frame--;
	else if (frame < 150)
		frame++;
	else if (sstate && *slider == 1)
		*slider = 2;
	if (*slider == 2 && frame == 0)
		*slider = 0;
	boxRGBA(render, (screen.x * 2 - (frame * 4)), 0, screen.x * 2 + 100, screen.y, 0, 0, 0, 150);
}

void			event_manager(SDL_Renderer *render, const Uint8 *kb_state, t_visu *venv)
{
	static int	help = 0;
	static int	slider = 0;

	if (!render)
		return ;
	SDL_PumpEvents();
	event_move(kb_state, venv);
	event_zoom(kb_state, venv);
	if ((kb_state[SDL_SCANCODE_H] || kb_state[SDL_SCANCODE_F1]) && !help)
		help = 1;
	if (kb_state[SDL_SCANCODE_S] && !slider)
		slider = 1;
	if (help)
		get_help(render, kb_state, &help);
	if (slider)
		get_slider(render, kb_state[SDL_SCANCODE_S], &slider, venv->screen);
/*	if (kb_state[SDL_SCANCODE_KP_MINUS] || kb_state[SDL_SCANCODE_KP_PLUS])
	{
		venv->morigin.x = venv->zoommod == DIV ? \
		(((venv->max.x / venv->zoom) - (venv->min.x / venv->zoom)) / 2) + \
		((venv->min.x / venv->zoom) + venv->offset.x) : (((venv->max.x * venv->zoom) - \
		(venv->min.x * venv->zoom)) / 2) + ((venv->min.x * venv->zoom) + venv->offset.x);
		venv->morigin.y = venv->zoommod == DIV ? \
		(((venv->max.y / venv->zoom) - (venv->min.y / venv->zoom)) / 2) + \
		((venv->min.y / venv->zoom) + venv->offset.y) : (((venv->max.y * venv->zoom) - \
		(venv->min.y * venv->zoom)) / 2) + ((venv->min.y * venv->zoom) + venv->offset.y);
		venv->offset.x = venv->origin.x - venv->morigin.x;
		venv->offset.y = venv->origin.y - venv->morigin.y;


		venv->offset.x = venv->zoommod == DIV ? \
		(venv->offset.x / venv->zoom) : (venv->offset.x * venv->zoom);
		venv->offset.y = venv->zoommod == DIV ? \
		(venv->offset.y / venv->zoom) : (venv->offset.y * venv->zoom);
	}*/
}
