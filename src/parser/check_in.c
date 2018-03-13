/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:49:56 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/20 19:00:03 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

static int	check_ants(char *line, int *mode, t_env *env)
{
	int		i;
	int		n_ants;

	i = 0;
	(*mode)++;
	while (ft_isdigit(line[i]))
		i++;
	if (!line[i] && (n_ants = ft_atoi(line)) > 0)
	{
		env->nb_ants = n_ants;
		env->antleft = n_ants;
	}
	else
		lem_in_error(ANTS, 'q', env);
	return (0);
}

static int	check_room(t_room **ret, char *line, t_env *env)
{
	int		i;
	int		j;
	char	**room;

	j = 0;
	if (!(room = ft_split_whitespaces(line)))
		lem_in_error(DEFAULT, 'q', env);
	else if (ft_strtablen(room) == 3 && \
	!ft_strchr(room[0], '-') && room[0][0] != 'L')
	{
		while (room[++j])
		{
			i = room[j][0] == '-' ? 1 : 0;
			while (ft_isdigit(room[j][i]))
				i++;
			if (room[j][i])
				return (1);
		}
		*ret = new_room(room[0], ft_atoi(room[1]), ft_atoi(room[2]), env);
		del_strtab_except(&room, 0);
		return (0);
	}
	del_strtab(&room);
	return (1);
}

static int	check_pipe(char *line, int *mode, t_env *env)
{
	char	**pipe;
	t_room	*one;
	t_room	*two;

	if ((*mode & 4) || (*mode & 8))
		return (1);
	if (!(*mode & 2))
		*mode = (*mode | 2);
	if (ft_strcmp(line, "-"))
	{
		if (!(pipe = ft_strsplit(line, '-')))
			lem_in_error(DEFAULT, 'q', env);
		else if (ft_strtablen(pipe) == 2)
			if ((one = search_room(pipe[0], env->rooms)) && \
			(two = search_room(pipe[1], env->rooms)))
			{
				add_pipe(&(one->pipes), two, env);
				add_pipe(&(two->pipes), one, env);
				del_strtab(&pipe);
				return (0);
			}
		del_strtab(&pipe);
	}
	return (1);
}

static int	check_cmd(int *mode, t_room *room, t_env *env)
{
	if (!(*mode & 4) && !(*mode & 8))
		return (0);
	if ((*mode & 4))
	{
		if (env->start)
			return (1);
		env->start = room;
		*mode = (*mode ^ 4);
	}
	if ((*mode & 8))
	{
		env->end = room;
		*mode = (*mode ^ 8);
	}
	return (0);
}

int			check_in(char *line, t_env *env)
{
	t_room		*ret;
	static int	mode = 0;

	ret = NULL;
	if (!line)
		return (1);
	if (line[0] == '#')
	{
		if (!ft_strcmp(line, "##start") && !(mode & 4))
			mode = (mode | 4);
		if (!ft_strcmp(line, "##end") && !(mode & 8))
			mode = (mode | 8);
		return (0);
	}
	else if (!line[0])
		return (1);
	else if (mode == 0)
		return (check_ants(line, &mode, env));
	else if ((mode & 1) && !(mode & 2) && !check_room(&ret, line, env))
		return (check_cmd(&mode, ret, env));
	else
		return (check_pipe(line, &mode, env));
}
