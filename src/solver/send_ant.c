/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:12:20 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/12 13:45:22 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "solver.h"

static void	real_res(t_env *env, char *res, int reset, int i)
{
	static unsigned int	taille = 1;
	long unsigned		index;
	long unsigned		j;
	char				*tmp;

	if (reset == 1 && (taille = 1))
		env->result[i] = memalloc_exit(400);
	if (reset == 0 && (index = -1))
	{
		while (env->result[i][index + 1])
			index++;
		if ((index + ft_strlen(res) + 1 >= taille * 400) && (j = -1))
		{
			tmp = env->result[i];
			env->result[i] = memalloc_exit(++taille * 400);
			while (tmp[++j])
				env->result[i][j] = tmp[j];
			ft_memdel((void **)tmp);
		}
		j = -1;
		while (res[++j])
			env->result[i][++index] = res[j];
		env->result[i][++index] = ' ';
		ft_memdel((void**)&res);
	}
}

void		select_ant(t_path *path, t_room *room, t_env *env, unsigned long i)
{
	if (room->next == env->end && (room->ant || path->room == env->start))
	{
		if (room->ant)
			real_res(env, create_string(room->ant, env->end->name), 0, i);
		else
		{
			real_res(env, create_string(++env->nb_ants, env->end->name), 0, i);
			--path->nb_ant;
		}
		room->ant = 0;
		env->antleft--;
	}
	if (room->prev == env->start && path->nb_ant > 0 && room->ant == 0)
	{
		real_res(env, create_string(++env->nb_ants, room->name), 0, i);
		room->ant = env->nb_ants;
		--path->nb_ant;
	}
	if ((room != env->start) && room->prev->ant)
	{
		real_res(env, create_string(room->prev->ant, room->name), 0, i);
		room->ant = room->prev->ant;
		room->prev->ant = 0;
	}
}

void		launch_ant(t_env *env)
{
	t_path			*tmp;
	t_room			*room;
	unsigned long	nb_tour;

	nb_tour = -1;
	env->antleft = env->nb_ants;
	env->nb_ants = 0;
	ft_printf("\n");
	while (env->antleft > 0)
	{
		real_res(env, "", 1, ++nb_tour);
		tmp = env->paths;
		while (tmp)
		{
			room = tmp->room;
			while (room && (room != env->start || tmp->room == env->start))
			{
				select_ant(tmp, room, env, nb_tour);
				room = room->prev;
			}
			tmp = tmp->prev;
		}
		ft_printf("%s\n", env->result[nb_tour]);
	}
}

static int	cnt_max_tour(t_path *tmp, long double value,
	unsigned long nb_path, t_env *env)
{
	unsigned long max_tour;

	max_tour = 0;
	while (tmp)
	{
		if ((long)((unsigned long)(value / nb_path + 0.5) - tmp->length) > 0)
		{
			env->ant_live++;
			tmp->nb_ant = (unsigned long)(value / nb_path + 0.5) - tmp->length;
			value -= ((unsigned long)(value / nb_path + 0.5));
			if (max_tour < tmp->nb_ant + tmp->length)
				max_tour = tmp->nb_ant + tmp->length;
		}
		else
			value -= tmp->length;
		nb_path--;
		tmp = tmp->prev;
	}
	return (max_tour);
}

void		release_ants(t_env *env)
{
	t_path			*tmp;
	long double		value;
	unsigned long	nb_path;
	unsigned long	max_tour;

	max_tour = 0;
	if ((env->paths && env->paths->room) ||
	(env->paths->prev && env->paths->prev->room))
	{
		if (!(env->paths && env->paths->room))
			env->paths = env->paths->prev;
		tmp = env->paths;
		value = env->nb_ants;
		nb_path = 0;
		while (tmp)
		{
			value += tmp->length;
			++nb_path;
			tmp = tmp->prev;
		}
		max_tour = cnt_max_tour(env->paths, value, nb_path, env);
		env->result = memalloc_exit(sizeof(char *) * max_tour);
		launch_ant(env);
	}
}
