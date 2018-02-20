/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:06:36 by gcollett          #+#    #+#             */
/*   Updated: 2018/02/20 20:08:20 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

void	lock_path(t_env *env);
void	reset_room(t_env *env);
char	*create_string(unsigned long nb_ant, char *room);
int		save_info(int set, int new_depth, t_room *o_room, t_env *env);

#endif
