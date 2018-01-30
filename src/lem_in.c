/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/03 18:50:11 by vsporer          ###   ########.fr       */
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
	get_path(&env);
	if (env.paths->room)
		release_ants(&env);
	else
	{
		write(1, "ERROR No path\n", 14);
		return(0);
	}
	if (ac == 2 && !ft_strcmp(av[1], "-v"))
		lem_in_visu(&env);
	//del_room_tab(env.rooms);
	// si youva peux me confirmer que ca boucle bien on a a peux pret le meme
	//nombre de reponse que felix.
	return (0);
}
