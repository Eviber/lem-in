/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:41:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/01/04 18:08:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu.h"
#include "libft.h"

static void	put_ants(t_env *env, t_room *pathroom)
{
	t_room	*cur;

	cur = pathroom;
	while (cur->prev != env->start)
	{
		if (cur->prev->ant)
		{
			cur->ant = cur->prev->ant;
			ft_printf("L%d-%s ", cur->ant, cur->name);
		}
		cur = cur->prev;
	}
	if (env->antleft)
	{
		cur->ant = env->nb_ants - env->antleft;
		ft_printf("L%d-%s ", cur->ant, cur->name);
		env->antleft--;
	}
}

void		output(t_env *env, int v)
{
	int		lem_out;

	lem_out = 0;
	while (lem_out < env->nb_ants)
	{
		if (env->paths[0]->room->ant)
		{
			ft_printf("L%d-%s ", env->paths[0]->room->ant, env->paths[0]->room->name);
			lem_out++;
		}
		put_ants(env, env->paths[0]->room);
		ft_putchar('\n');
		if (v)
			v = visu();
	}
}
