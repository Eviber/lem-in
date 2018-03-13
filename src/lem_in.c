/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/12 13:53:42 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "visu_lem_in.h"

static void		print_map(char **input, t_env *env)
{
	int		i;

	i = -1;
	get_path(env);
	if (!env->paths->room || env->end == env->start)
	{
		if (env->paths->room)
			write(2, "Start and End is the same room.\n", 28);
		else
			write(2, "ERROR No path\n", 14);
		exit(1);
	}
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
	print_map(read_map(&env), &env);
	release_ants(&env);
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		lem_in_visu(&env);
	del_room_tab(env.rooms);
	return (0);
}
