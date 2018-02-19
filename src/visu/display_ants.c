/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 14:25:08 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/02 19:11:34 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static int	create_ant(SDL_Renderer *render, int i, char *ant, t_visu *venv)
{
	SDL_Rect		pos;
	SDL_Color		color;
	SDL_Surface		*surf;
	SDL_Texture		*text;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	if (!(surf = TTF_RenderText_Solid(venv->font, ant, color)))
		return (1);
	if (!(text = SDL_CreateTextureFromSurface(render, surf)))
		return (1);
	pos.w = surf->w;
	pos.h = surf->h;
	pos.x = venv->pos[i].x - pos.w / 2;
	pos.y = venv->pos[i].y - pos.h / 2;
	SDL_FreeSurface(surf);
	if (SDL_RenderCopy(render, text, NULL, &pos))
		return (1);
	SDL_DestroyTexture(text);
	return (0);
}

int			display_ants(SDL_Renderer *render, t_visu *venv)
{
	int		i;
	char	**line;
	char	**room;

	i = -1;
	if (!(line = ft_strsplit(venv->step_list[venv->i], ' ')))
		return (1);
	while (line[++i])
	{
		if (!(room = ft_strsplit(line[i], '-')))
			return (1);
		if (search_room(room[1], venv->rooms) != venv->end)
			if (create_ant(render, get_room_index(venv->rooms, \
			search_room(room[1], venv->rooms)), room[0], venv))
				return (1);
		ft_strdel(&room[0]);
		ft_strdel(&room[1]);
		ft_memdel((void**)&room);
		ft_strdel(&line[i]);
	}
	ft_memdel((void**)&line);
	return (0);
}
