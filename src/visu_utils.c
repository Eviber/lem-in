/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:31:53 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/13 14:14:32 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "visu.h"

SDL_Texture		*strtotex(char *str, t_winenv env, TTF_Font *f)
{
	SDL_Texture		*tex;
	SDL_Surface		*surf;
	SDL_Color		color;

	color = (SDL_Color){255, 255, 255, 255};
	surf = TTF_RenderText_Blended(f, str, color);
	if (!surf)
		panic("Failed creating text surface", SDL_GetError());
	tex = SDL_CreateTextureFromSurface(env.render, surf);
	if (!tex)
		panic("Failed converting surface to texture", SDL_GetError());
	SDL_FreeSurface(surf);
	return (tex);
}

double				dist(double x1, double y1, double x2, double y2)
{
	double		dx;
	double		dy;

	dx = x1 - x2;
	dy = y1 - y2;
	return (fabs(sqrt(dx * dx + dy * dy)));
}

int					panic(const char *str, const char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str2, 2);
	return (0);
}

t_winenv			*getsdlenv(t_env *colony)
{
	static t_winenv	*winenv = NULL;

	if (!winenv && colony)
		if ((winenv = (t_winenv *)ft_memalloc(sizeof(t_winenv))))
		{
			winenv->colony = colony;
			winenv->redraw = 1;
		}
	return (winenv);
}

int					quitvisu(t_winenv *env)
{
	if (!env || env->quit)
	{
		SDL_Quit();
		return (0);
	}
	return (1);
}
