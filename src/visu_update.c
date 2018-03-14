/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/14 11:25:24 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lemin.h"
#include "visu.h"

void				updatelast(t_winenv *w, t_env colony)
{
	int				i;

	if (!w->lastants)
	{
		i = 0;
		while (colony.paths[i]->room)
			i++;
		w->lastants = (size_t *)ft_memalloc(i * sizeof(size_t));
		if (!w->lastants)
		{
			panic("Malloc error\n", "");
			return ;
		}
	}
	i = 0;
	while (colony.paths[i] && colony.paths[i]->room)
	{
		w->lastants[i] = colony.paths[i]->room->ant;
		i++;
	}
}

void				visu_update(SDL_Renderer *render, t_env colony, t_winenv *w)
{
	if (w->redraw)
	{
		cleartex(render, w->layer[TUBES]);
		cleartex(render, w->layer[ROOMS]);
	}
	if (w->wait || w->redraw)
		cleartex(render, w->layer[ANTS]);
	visu_putall(render, colony, w);
	SDL_SetRenderTarget(render, NULL);
	SDL_RenderCopy(render, w->layer[TUBES], NULL, NULL);
	SDL_RenderCopy(render, w->layer[ROOMS], NULL, NULL);
	SDL_RenderCopy(render, w->layer[ANTS], NULL, NULL);
	counter(colony, *w);
}
