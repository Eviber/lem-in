/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:59:46 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/18 00:52:22 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
#include <eparser.h>

static t_env			init_antfarm(void)
{
	t_env				ret;

	ret.start = NULL;
	ret.end = NULL;
	ret.paths = NULL;
	ret.rooms = NULL;
	ret.nb_ants = -1;
	ret.antleft = -1;
	return (ret);
}

int						main(void)
{
	t_env				antfarm;

	antfarm = init_antfarm();
	if (!parse_antfarm(&antfarm))
		ft_printf("ERROR\n");
	else
	{
		ft_printf("Okay!\n");
//		solver(&antfarm);
//		output(&antfarm);
	}
	return (0);
}
