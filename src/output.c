/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:41:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/01/18 17:38:55 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu.h"
#include "libft.h"

static void	put_ants(t_env *env, t_room *pathroom)
{
	t_room	*cur;

	cur = pathroom;
	while (cur && cur->prev && cur->prev != env->start)
	{
		if (cur->prev->ant)
		{
			cur->ant = cur->prev->ant;
			ft_printf("L%d-%s ", cur->ant, cur->name);
			cur->prev->ant = 0;
		}
		cur = cur->prev;
	}
	if (cur && env->antleft)
	{
		cur->ant = env->nb_ants - env->antleft + 1;
		if (cur != env->start)
			ft_printf("L%d-%s ", cur->ant, cur->name);
		env->antleft--;
	}
}

void		output(t_env *env, int v)
{
	int		lem_out;
	int		i;

	lem_out = 0;
	while (lem_out < env->nb_ants)
	{
		i = 0;
		while (env->paths[i])
		{
			if (env->paths && env->paths[i] && env->paths[i]->room && env->paths[i]->room->ant)
			{
				ft_printf("L%d-%s ", env->paths[i]->room->ant, env->end->name);
				env->paths[i]->room->ant = 0;
				lem_out++;
			}
			put_ants(env, env->paths[i]->room);
			i++;
		}
		if (v)
			v = visu();
		ft_putchar('\n');
	}
	while (v)
		v = visu();
}
