/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:24:50 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/27 15:58:45 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static int		create_room_name(SDL_Renderer *render, int i, t_visu *venv)
{
	SDL_Rect		pos;
	SDL_Color		color;
	SDL_Surface		*surf;
	SDL_Texture		*text;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	if (!(surf = TTF_RenderText_Solid(venv->font, venv->rooms[i]->name, color)))
		return (1);
	if (!(text = SDL_CreateTextureFromSurface(render, surf)))
		return (1);
	pos.w = surf->w;
	pos.h = surf->h;
	pos.x = venv->pos[i].x - pos.w / 2;
	pos.y = venv->pos[i].y - 80;
	SDL_FreeSurface(surf);
	if (SDL_RenderCopy(render, text, NULL, &pos))
		return (1);
	SDL_DestroyTexture(text);
	return (0);
}

void			get_rooms_name(SDL_Renderer *render, int *rooms, t_visu *venv)
{
	int		i;

	i = -1;
	if (!venv->kb_state[SDL_SCANCODE_R] && *rooms == 1)
		*rooms = 2;
	else if (venv->kb_state[SDL_SCANCODE_R] && *rooms == 2)
		*rooms = 3;
	else if (!venv->kb_state[SDL_SCANCODE_R] && *rooms == 3)
		*rooms = 0;
	else
	{
		while (venv->rooms[++i])
		{
			if (create_room_name(render, i, venv))
				return ;
		}
	}
	SDL_RenderCopy(render, venv->step, NULL, &venv->step_size);
}
