/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:00:45 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/15 10:42:34 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <SDL2_gfxPrimitives.h>
#include "libft.h"
#include "visu.h"

static int	tmptorgb(double tmp, double t1, double t2)
{
	double	res;

	if (6 * tmp < 1)
		res = t2 + (t1 - t2) * 6 * tmp;
	else if (2 * tmp < 1)
		res = t1;
	else if (3 * tmp < 2)
		res = t2 + (t1 - t2) * (2.0 / 3.0 - tmp) * 6;
	else
		res = t2;
	return ((int)lround(res * 255));
}

SDL_Color	hsl(int h, double s, double l)
{
	SDL_Color	res;
	double		t1;
	double		t2;

	h %= 360;
	s = s / 100.0;
	l = l / 100.0;
	t1 = (l < 0.5) ? l * (1 + s) : l + s - l * s;
	t2 = 2 * l - t1;
	res.a = 255;
	res.r = tmptorgb((double)((h + 120) % 360) / 360, t1, t2);
	res.g = tmptorgb((double)h / 360, t1, t2);
	res.b = tmptorgb((double)((h - 120 + 360) % 360) / 360, t1, t2);
	return (res);
}

void		debuglock(t_winenv w, t_pos pos, t_room *room)
{
	SDL_Rect	dst;
	SDL_Color	color;

	color = hsl(room->locked * 2 * 360 / 5, 100, 50);
	SDL_SetRenderTarget(w.render, w.layer[TUBES]);
	if (room->next)
	{
		dst.x = room->next->pos.x * w.zoom + w.mov.x;
		dst.y = room->next->pos.y * w.zoom + w.mov.y;
		thickLineRGBA(w.render, pos.x, pos.y, dst.x, dst.y, 10,
								color.r, color.g, color.b, 255);
	}
	if (room->prev)
	{
		dst.x = room->prev->pos.x * w.zoom + w.mov.x;
		dst.y = room->prev->pos.y * w.zoom + w.mov.y;
		thickLineRGBA(w.render, pos.x, pos.y, dst.x, dst.y, 10,
								color.r, color.g, color.b, 255);
	}
}

void		debugroom(t_winenv w, t_pos pos, t_room *room)
{
	SDL_Rect	dst;
	SDL_Texture	*tex;
	char		*str;

	if (room->locked >= 1)
		debuglock(w, pos, room);
	SDL_SetRenderTarget(w.render, w.layer[ROOMS]);
	str = ft_itoa(room->weight);
	filledCircleColor(w.render, pos.x, pos.y, 30, 0xFF009900);
	if (room == w.head)
		filledCircleColor(w.render, pos.x, pos.y, 50, 0x99FFFFFF);
	if ((tex = strtotex(str, w, w.font)))
	{
		free(str);
		dst.x = pos.x - 15;
		dst.y = pos.y - 15;
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
		SDL_RenderCopy(w.render, tex, NULL, &dst);
		SDL_DestroyTexture(tex);
	}
}

void		visu_debug(int state)
{
	t_winenv	*w;

	w = getsdlenv(NULL);
	w->debug = state;
	w->redraw = 1;
}
