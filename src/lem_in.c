/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/31 15:18:46 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser_lem-in.h"

int				main(void)
{
	int		i;
	t_env	env;

	i = -1;
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
	del_room_tab(env.rooms);
	return (0);
}
