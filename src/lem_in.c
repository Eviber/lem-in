/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/25 20:59:18 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser_lem-in.h"
#include "visu_lem-in.h"

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
//	check_map(&env);
//	get_path(&env);
//	release_ants(&env);
	while (env.rooms && (env.rooms)[++i])
	{
		ft_printf("Name: %s - Pos: x = %d; y = %d - First pipe: %s", \
		((env.rooms)[i])->name, ((env.rooms)[i])->pos.x, \
		((env.rooms)[i])->pos.y, ((((env.rooms)[i])->pipes)[0])->name);
		if ((env.rooms)[i] == env.start)
			ft_putstr(" - Start");
		if ((env.rooms)[i] == env.end)
			ft_putstr(" - End");
		ft_putendl("");
	}
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		lem_in_visu(&env);
	del_room_tab(env.rooms);
	return (0);
}
