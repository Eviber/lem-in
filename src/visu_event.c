/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:39:24 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/19 17:23:31 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>

#include "lemin.h"
#include "visu.h"

static int			event_zoom(t_winenv *env, const Uint8 *state)
{
	double			zoomval;

	if (state[SDL_SCANCODE_KP_PLUS])
	{
		zoomval = 1.1;
		env->mov.x = (long)(env->mov.x - env->dispmode.w / 2) *
					(env->zoom * zoomval) / env->zoom + env->dispmode.w / 2;
		env->mov.y = (long)(env->mov.y - env->dispmode.h / 2) *
					(env->zoom * zoomval) / env->zoom + env->dispmode.h / 2;
		env->zoom *= zoomval;
	}
	if (state[SDL_SCANCODE_KP_MINUS] && env->zoom * 0.9 > 0)
	{
		zoomval = 0.9;
		env->mov.x = (long)(env->mov.x - env->dispmode.w / 2) *
					(env->zoom * zoomval) / env->zoom + env->dispmode.w / 2;
		env->mov.y = (long)(env->mov.y - env->dispmode.h / 2) *
					(env->zoom * zoomval) / env->zoom + env->dispmode.h / 2;
		env->zoom *= zoomval;
	}
	return (state[SDL_SCANCODE_KP_PLUS] ^ state[SDL_SCANCODE_KP_MINUS]);
}

static int			event_move(t_winenv *env, const Uint8 *state)
{
	SDL_Point		m;
	t_pos			tmp;

	tmp = env->mov;
	if (SDL_GetRelativeMouseState(&(m.x), (&m.y)) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		env->mov.x += m.x;
		env->mov.y += m.y;
	}
	else
	{
		env->mov.y += ((SDL_GetTicks() - env->frameticks)) *
					((state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) -
					(state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]));
		env->mov.x += ((SDL_GetTicks() - env->frameticks)) *
					((state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) -
					(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]));
	}
	if (state[SDL_SCANCODE_RETURN])
	{
		env->mov = (t_pos){env->dispmode.w / 2, env->dispmode.h / 2};
		env->zoom = env->orig_zoom;
	}
	return (state[SDL_SCANCODE_RETURN] || tmp.x != env->mov.x ||
			tmp.y != env->mov.y || m.x || m.y);
}

int					handle_event(t_winenv *env)
{
	const Uint8		*state;

	state = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	env->redraw |= event_zoom(env, state) || event_move(env, state) ||
					state[SDL_SCANCODE_TAB] ^ env->putnames;
	env->putnames = state[SDL_SCANCODE_TAB];
	env->offticks += (!env->debug && state[SDL_SCANCODE_LSHIFT]) ? 20 : 0;
	if (env->debug)
		env->wait = (state[SDL_SCANCODE_LSHIFT]) ? 20 : 500;
	else
		env->wait = 100 * (!state[SDL_SCANCODE_LSHIFT]);
	while (state[SDL_SCANCODE_SPACE])
		SDL_PumpEvents();
	env->quit |= state[SDL_SCANCODE_Q] || state[SDL_SCANCODE_ESCAPE] ||
				SDL_QuitRequested();
	return (env->quit);
}
