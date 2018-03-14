/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/14 21:21:51 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lemin.h"
#include "visu.h"

void				cleartex(SDL_Renderer *render, SDL_Texture *tex)
{
	SDL_SetRenderTarget(render, tex);
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_NONE);
	SDL_RenderClear(render);
}
 
void				visu_putall(SDL_Renderer *render, t_env colony, t_winenv *w)
{
	t_room			**rooms;
	int				i;

	i = 0;
	rooms = colony.rooms;
	while (rooms[i])
	{
		if (rooms[i]->pipes)
			putpipes(render, *(rooms[i]), *w);
		putroom(*w, rooms[i], colony);
		i++;
	}
}

int					visu()
{
	t_winenv		env;

	while (!handle_event(env))
	{
		visu_update(env->render, *(env->colony), env);
	}
	return (quitvisu(env));
}
