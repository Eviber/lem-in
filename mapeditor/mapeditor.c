/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapeditor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:31:20 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/14 21:54:10 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include "libft.h"
#include "lemin.h"
#include "eparser.h"
#include "solver.h"
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

t_room				*find_room(t_env *antfarm, char *name)
{
	t_room			**rooms;

	rooms = antfarm->rooms;
	while (name && rooms && *rooms)
	{
		if ((*rooms)->name && !ft_strcmp(name, (*rooms)->name))
			return (*rooms);
		rooms++;
	}
	return (NULL);
}

static t_env		init_antfarm(void)
{
	t_env			ret;

	ret.start = NULL;
	ret.end = NULL;
	ret.paths = NULL;
	ret.rooms = NULL;
	ret.nb_ants = -1;
	ret.antleft = -1;
	ret.nb_rooms = 0;
	ret.to_print = NULL;
	return (ret);
}

int		main(int argc, char **argv)
{
	t_winenv		env;
	t_env			antfarm;

	antfarm = init_antfarm();
	if (!parse_antfarm(&antfarm))
	{
		ft_putstr_fd("ERROR\n", 2);
		return (-1);
	}
	else if (!visu_init(&antfarm))
	{
		ft_putstr_fd("Visualizer failed.\n", 2);
		return (-1);
	}
	while (!handle_event(env))
	{
		visu_update(env->render, *(env->colony), env);
	}
	free_antfarm(&antfarm);
	return (quitvisu(env));
}
