/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/13 19:15:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lemin.h"
#include "visu.h"

void				putlast(t_winenv *w, t_env colony)
{
	int				i;

	i = 0;
	while (w->lastants && colony.paths[i] && colony.paths[i]->room)
	{
		if (w->lastants[i])
			putant(*w, colony.end, colony.paths[i]->room, w->lastants[i]);
		i++;
	}
}

void				putroomname(t_winenv w, char *roomname, t_pos pos)
{
	SDL_Rect	dst;
	SDL_Texture	*tex;

	SDL_GetMouseState(&dst.x, &dst.y);
	if ((w.putnames || dist(dst.x, dst.y, pos.x, pos.y) < 100) &&
		(tex = strtotex(roomname, w, w.font)))
	{
		dst.x = pos.x;
		dst.y = pos.y;
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(w.render, tex, NULL, &dst);
		SDL_DestroyTexture(tex);
	}
}

void				putroom(t_winenv w, t_room *room, t_env colony)
{
	t_pos			pos;

	SDL_SetRenderTarget(w.render, w.layer[ROOMS]);
	pos.x = room->pos.x * w.zoom + w.mov.x;
	pos.y = room->pos.y * w.zoom + w.mov.y;
	filledCircleColor(w.render, pos.x, pos.y, 33, 0xFF78726F);
	if (room == colony.start && room == colony.end)
		filledCircleRGBA(w.render, pos.x, pos.y, 30, 200, 200, 200,
							SDL_ALPHA_OPAQUE);
	else if (room == colony.start)
		filledCircleColor(w.render, pos.x, pos.y, 30, 0xFFBCBA00);
	else if (room == colony.end)
		filledCircleRGBA(w.render, pos.x, pos.y, 30, 200, 200, 100,
							SDL_ALPHA_OPAQUE);
	else
		filledCircleColor(w.render, pos.x, pos.y, 30, 0xFF4C4846);
	putroomname(w, room->name, pos);
}

void				putpipes(SDL_Renderer *render, t_room room, t_winenv w)
{
	t_pos			orig;
	t_pos			dest;
	int				i;

	SDL_SetRenderTarget(render, w.layer[TUBES]);
	orig.x = room.pos.x * w.zoom + w.mov.x;
	orig.y = room.pos.y * w.zoom + w.mov.y;
	i = 0;
	while (room.pipes[i])
	{
		dest.x = room.pipes[i]->pos.x * w.zoom + w.mov.x;
		dest.y = room.pipes[i]->pos.y * w.zoom + w.mov.y;
		thickLineRGBA(render, orig.x, orig.y, dest.x, dest.y,
				10, 255, 255, 255, 50);
		i++;
	}
}

void				putcount(t_winenv env, char *str, SDL_Rect *rect)
{
	SDL_Texture		*tex;

	tex = strtotex(str, env, env.bigfont);
	SDL_QueryTexture(tex, NULL, NULL, &rect->w, &rect->h);
	SDL_RenderCopy(env.render, tex, NULL, rect);
	SDL_DestroyTexture(tex);
	free(str);
}
