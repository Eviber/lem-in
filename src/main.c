/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:59:46 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/16 23:50:13 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "eparser.h"
#include "visu.h"

static t_env			init_antfarm(void)
{
	t_env				ret;

	ret.start = NULL;
	ret.end = NULL;
	ret.paths = NULL;
	ret.rooms = NULL;
	ret.nb_ants = 0;
	ret.antleft = 0;
	return (ret);
}

int						main(void)
{
	t_env				antfarm;
	int		v;

	v = 1;
	antfarm = init_antfarm();
	if (!get_antfarm(&antfarm))
		ft_printf("ERROR\n");
	else
		ft_printf("Okay!\n");
//	{
//		solver(&antfarm);
//		output(&antfarm);
//	}
	ft_printf("Okay 2!\n");
	if (0 && !visu_init(&antfarm))
	{
		ft_putstr_fd("Visualizer failed.\n", 2);
		v = 0;
	}
//	ft_printf("Okay 3!\n");
	while (0 && v)
	{
		v = visu();
		if (0)
		{
			SDL_Delay(500);
			v = visu();
		}
	}
	return (0);
}
