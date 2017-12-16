/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:38 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/16 20:09:23 by vsporer          ###   ########.fr       */
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
		printf("Name: %s - Pos: x = %d; y = %d - First pipe: %s\n", \
		((env.rooms)[i])->name, ((env.rooms)[i])->pos.x, \
		((env.rooms)[i])->pos.y, ((((env.rooms)[i])->pipes)[0])->name);
	del_room_tab(env.rooms);
	return (0);
}
