/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/20 18:54:14 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "visu_lem_in.h"

static void		print_map(char **input)
{
	int		i;

	i = -1;
	while (input && input[++i])
	{
		ft_putendl(input[i]);
		ft_strdel(&(input[i]));
	}
	ft_memdel(((void**)&input));
}

int				main(int ac, char **av)
{
	int		i;
	t_env	env;

	i = -1;
	if (ac > 2 || (ac == 2 && ft_strcmp(av[1], "-v")))
	{
		ft_putendl_fd("usage: ./lem-in [-v]", 2);
		return (1);
	}
	print_map(read_map(&env));
	get_path(&env);
	if (env.paths->room && env.end != env.start)
		release_ants(&env);
	else
	{
		if (env.paths->room)
			write(2, "\nStart and End is same room all the ant has arrived\n", 52);
		else
			write(2, "ERROR No path\n", 14);
		return (0);
	}
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		lem_in_visu(&env);
	del_room_tab(env.rooms);
	return (0);
}
