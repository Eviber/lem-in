/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:41:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/02/08 15:51:35 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "visu.h"
#include "libft.h"

static void				mov_ants(t_env *env, t_room *pathroom)
{
	t_room				*cur;

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

static int				getroomfromant(t_env *env, unsigned long *lasts,
						t_room *tofill, unsigned long target)
{
	int					i;
	int					j;

	i = 0;
	j = 0;
	while (env->rooms[i] && (unsigned long)env->rooms[i]->ant != target)
		i++;
	while (env->rooms[i] && env->paths[j] && lasts[j] != target)
		j++;
	if (env->rooms[i] && lasts[j] != target )
		*tofill = (env->rooms[i]) ? *(env->rooms[i]) : *(env->paths[j]->room);
	else
		return (FALSE);
	return (TRUE);
}

static unsigned long	putants(t_env *env, unsigned long min,
						unsigned long *lasts)
{
	t_room				tofill;
	unsigned long		target;

	target = min;
	while (target <= (unsigned long)env->nb_ants - (unsigned long)env->antleft)
	{
		if (getroomfromant(env, lasts, &tofill, target))
			ft_printf("L%d-%s ", target, tofill.name);
		else if (target == min)
			min++;
		target++;
	}
	return (min);
}

static void				sub_output(t_env *env, int v, unsigned long *lasts,
						unsigned long min)
{
	int					i;

	while (env->lem_out < env->nb_ants)
	{
		i = 0;
		ft_putchar('\n');
		while (env->paths[i])
		{
			if (env->paths[i]->room)
				lasts[i] = (unsigned long)(env->paths[i]->room->ant);
			if (env->paths && env->paths[i]
				&& env->paths[i]->room && env->paths[i]->room->ant)
			{
				ft_printf("L%d-%s ",  env->paths[i]->room->ant, env->end->name);
				env->paths[i]->room->ant = 0;
				env->lem_out++;
			}
			mov_ants(env, env->paths[i]->room);
			i++;
		}
		if (v)
			v = visu();
		min = putants(env, min, lasts);
	}
	ft_putchar('\n');
}

void					output(t_env *env, int v)
{
	unsigned long		*lasts;
	unsigned long		min;
	int					i;

	min = 1;
	env->lem_out = 0;
	env->antleft = env->nb_ants;
	i = 0;
	while (env->paths && env->paths[i] && env->paths[i]->room)
		i++;
	lasts = (unsigned long *)ft_memalloc((i + 1) * sizeof(long));
	sub_output(env, v, lasts, min);
	free(lasts);
	while (v)
		v = visu();
}
