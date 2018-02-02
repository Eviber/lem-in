/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:41:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/02 19:38:51 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu.h"
#include "libft.h"

static void	mov_ants(t_env *env, t_room *pathroom)
{
	t_room	*cur;

	cur = pathroom;
	while (cur && cur->prev && cur->prev != env->start)
	{
		if (cur->prev->ant)
		{
			cur->ant = cur->prev->ant;
			cur->prev->ant = 0;
		}
		cur = cur->prev;
	}
	if (cur && env->antleft)
	{
		cur->ant = env->nb_ants - env->antleft + 1;
		env->antleft--;
	}
}

unsigned long	putants(t_env *env, unsigned long min)
{
	int				i;
	unsigned long	target;

	target = 1;
	while (target <= (unsigned long)env->lem_out)
	{
		i = 0;
//		ft_printf("%lu", target);
		while (env->rooms[i] && env->rooms[i]->ant != (long)target)
			i++;//ft_printf("|%lu|", env->rooms[i++]->ant);
		if (env->rooms[i])
			ft_printf("AL%d-%s ", target, env->rooms[i]->name);
		else if (target == min)
			min++;
		target++;
	}
	ft_putchar('\n');
	return (min);
}

void		output(t_env *env, int v)
{
	int				i;
	unsigned long	min;

	min = 1;
	env->lem_out = 0;
	env->antleft = env->nb_ants;
	while (env->lem_out < env->nb_ants)
	{
		i = 0;
		while (env->paths[i])
		{
			if (env->paths && env->paths[i]
				&& env->paths[i]->room && env->paths[i]->room->ant)
			{
				ft_printf("L%d-%s ", env->paths[i]->room->ant, env->end->name);
				env->paths[i]->room->ant = 0;
				env->lem_out++;
			}
			mov_ants(env, env->paths[i]->room);
			i++;
		}
		if (v)
			v = visu();
		min = putants(env, min);
	}
	while (v)
		v = visu();
}
