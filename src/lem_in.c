/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/31 19:01:49 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser_lem-in.h"

int		main(int ac, char **av)
{
	int		i;
	t_env	env;

	i = -1;
	if (ac > 2 || (ac == 2 && ft_strcmp(av[1], "-v")))
	{
		ft_putendl_fd(2, "usage: ./lem-in [-v]");
		return (1);
	}
	read_map(&env);
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
	if (ac == 2 && ft_strcmp(av[1], "-v"))
		lem_in_visu(&env);
	del_room_tab(env.rooms);
	return (0);
}
