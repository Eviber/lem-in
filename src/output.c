/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:41:26 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/12 23:28:52 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "visu.h"
#include "libft.h"

void	calc_tosend(t_env *env)
{
	int		i;
	int		nb_paths;
	int		total_len;
	int		meanlen;
	int		mod;

	total_len = 0;
	nb_paths = -1;
	while (env->paths[++nb_paths]->room)
	{
		printf("iroom = %s\n", env->paths[nb_paths]->room->name);
		total_len += env->paths[nb_paths]->length;
	}
	meanlen = (env->nb_ants + total_len) / nb_paths;
	mod = (env->nb_ants + total_len) % nb_paths;
	printf("(%lu + %d) / %d = %d\n", env->nb_ants, total_len, nb_paths, meanlen);
	i = -1;
	while (env->paths[++i]->room)
	{
		env->paths[i]->tosend = meanlen - env->paths[i]->length + (mod > 0);
		mod--;
		printf("path %d > %d\n", env->paths[i]->length, env->paths[i]->tosend);
	}
	env->paths[i - 1]->tosend = (meanlen - env->paths[i]->length);
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
			printf("AL%u-%s ", ant, env->paths[i]->start->name);
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
	if (ant == env->nb_ants - env->antleft + 1)
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
			printf("BL%lu-%s ", cur->ant, cur->next->name);
			if (cur->next == env->end)
				env->lem_out++;
			cur->ant = 0;
			return (1);
		}
	}
	return (1);
}

void	setfirst(t_env *env)
{
	t_room	*cur;
	int		i;

	i = 0;
	while (env->paths[i]->room)
	{
		cur = env->paths[i]->room;
		while (cur && cur->prev != env->start)
			cur = cur->prev;
		env->paths[i]->start = cur;
		i++;
	}
}

void	output(t_env *env, int v)
{
	unsigned int	i;

	// calc limit per path
	setfirst(env);
	calc_tosend(env);
	env->lem_out = 0;
	env->antleft = env->nb_ants;
	while (env->lem_out < env->nb_ants)
	{
		if (v)
			v = visu();
		i = 1;
		while (i <= env->nb_ants && mov_ant(env, i))
				i++;
		printf("\n");
	}
	while (v)
		v = visu();
}
/*
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
*/
