/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 20:37:35 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/21 21:49:10 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

int		ispathworth(t_env *env, int depth);

void	conflict(t_room *locked_room, t_env *env, long depth, t_room *origin);

int		check_conf(t_room *room, t_env *env);
int		find_shortest(t_env *env, int f_iter);
void	lock(t_env *env);

int		solve(t_env *env);
void	output(t_env *env);

#endif
