/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:08:13 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/16 19:55:17 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "solver.h"

static void		env_init(t_env *env)
{
	env->start = NULL;
	env->end = NULL;
	env->paths = NULL;
	env->rooms = NULL;
	env->conflit = memalloc_exit(sizeof(t_conflit));
	env->ant_live = 0;
	env->result = NULL;
	env->mean_len = 0;
	env->nb_path = 0;
	env->nb_ants = 0;
	env->nb_rooms = 0;
	env->antleft = 0;
	env->dp = 0;
	env->conflict = 0;
}

char			**read_map(t_env *env)
{
	char	*line;
	char	**input;

	line = NULL;
	input = NULL;
	env_init(env);
	while (get_next_line(0, &line) > 0 && !check_in(line, env))
	{
		if (ft_strtabadd(&input, line))
		{
			ft_strdel(&line);
			del_strtab(&input);
			lem_in_error(DEFAULT, 'q', env);
		}
		line = NULL;
	}
	ft_strdel(&line);
	return (input);
}
