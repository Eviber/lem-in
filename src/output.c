/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:41:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/22 09:28:42 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "visu.h"
#include "libft.h"

void					calc_tosend(t_env *env)
{
	int		i;
	int		nb_paths;
	int		total_len;
	int		meanlen;
	int		mod;

	total_len = 0;
	nb_paths = -1;
	while (env->paths[++nb_paths]->room)
		total_len += env->paths[nb_paths]->length;
	meanlen = (env->nb_ants + total_len) / nb_paths;
	mod = (env->nb_ants + total_len) % nb_paths;
	i = -1;
	while (env->paths[++i]->room)
	{
		env->paths[i]->tosend = meanlen - env->paths[i]->length + (mod > 0);
		mod--;
	}
}

static int				mov_new(t_env *env, unsigned int ant)
{
	int		i;

	i = 0;
	while (env->paths[i] && env->paths[i]->start)
	{
		if (!env->paths[i]->start->ant && env->paths[i]->tosend)
		{
			env->paths[i]->start->ant = env->nb_ants - env->antleft + 1;
			ft_printf("L%u-%s ", ant, env->paths[i]->start->name);
			env->antleft--;
			env->paths[i]->tosend--;
			return (1);
		}
		i++;
	}
	return (0);
}

static int				mov_ant(t_env *env, unsigned int ant)
{
	t_room				*cur;
	int					i;

	i = 0;
	if (env->paths[0]->start == env->start && ++env->lem_out)
		return (ft_printf("L%lu-%s ", ant, env->end->name));
	else if (ant == env->nb_ants - env->antleft + 1)
		return (mov_new(env, ant));
	cur = env->paths[0]->room;
	while (env->paths[i] && env->paths[i]->room)
	{
		cur = env->paths[i++]->room;
		while (cur && cur->ant != ant)
			cur = cur->prev;
		if (cur && cur->next)
		{
			cur->next->ant = cur->ant;
			ft_printf("L%lu-%s ", cur->ant, cur->next->name);
			if (cur->next == env->end)
				env->lem_out++;
			cur->ant = 0;
			return (1);
		}
	}
	return (1);
}

void					setfirst(t_env *env)
{
	t_room	*cur;
	int		i;

	i = 0;
	while (env->paths[i]->room)
	{
		cur = env->paths[i]->room;
		while (cur && cur != env->start && cur->prev != env->start)
			cur = cur->prev;
		env->paths[i]->start = cur;
		i++;
	}
}

void					output(t_env *env)
{
	unsigned int	i;

	if (env->v)
		visu_debug(0);
	setfirst(env);
	calc_tosend(env);
	env->lem_out = 0;
	env->antleft = env->nb_ants;
	ft_printf("\n");
	while (env->lem_out < env->nb_ants)
	{
		i = 1;
		while (i <= env->nb_ants && mov_ant(env, i))
			i++;
		ft_printf("\n");
		if (env->v)
			env->v = visu(NULL, NULL);
	}
	env->paths[0]->start = NULL;
	while (env->v)
		env->v = visu(NULL, NULL);
}
