/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 14:24:50 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/31 15:24:57 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static int		create_room_name(SDL_Renderer *render, int i, t_visu *venv)
{
	SDL_Rect		pos;
	SDL_Surface		*surf;
	SDL_Texture		*text;

	if (!(surf = TTF_RenderText_Solid(venv->font, venv->rooms[i]->name, \
	venv->txt_c)))
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

static int		start_end_display(SDL_Renderer *render, int i, t_visu *venv)
{
	char			*txt;
	SDL_Rect		pos;
	SDL_Surface		*surf;
	SDL_Texture		*text;

	if (venv->rooms[i] == venv->start && venv->rooms[i] == venv->end)
		txt = (char*)"START - END";
	else if (venv->rooms[i] == venv->start)
		txt = (char*)"START";
	else
		txt = (char*)"END";
	if (!(surf = TTF_RenderText_Solid(venv->font, txt, venv->txt_c)))
		return (1);
	if (!(text = SDL_CreateTextureFromSurface(render, surf)))
		return (1);
	pos.w = surf->w;
	pos.h = surf->h;
	pos.x = venv->pos[i].x - pos.w / 2;
	pos.y = venv->pos[i].y - 55;
	SDL_FreeSurface(surf);
	if (SDL_RenderCopy(render, text, NULL, &pos))
		return (1);
	SDL_DestroyTexture(text);
	return (0);
}

int				get_rooms_name(SDL_Renderer *render, int *rooms, t_visu *venv)
{
	int		i;

	i = -1;
	if (!venv->kb_state[SDL_SCANCODE_R] && *rooms == 1)
		*rooms = 2;
	else if (venv->kb_state[SDL_SCANCODE_R] && *rooms == 2)
		*rooms = 3;
	else if (!venv->kb_state[SDL_SCANCODE_R] && *rooms == 3)
		*rooms = 0;
	if (*rooms == 2 || *rooms == 3)
	{
		while (venv->rooms[++i])
		{
			if (create_room_name(render, i, venv))
				return (1);
			if (venv->rooms[i] == venv->start || venv->rooms[i] == venv->end)
				if (start_end_display(render, i, venv))
					return (1);
		}
	}
	return (0);
}
