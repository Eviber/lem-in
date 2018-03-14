/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:06:36 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/12 14:08:06 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

void	lock_path(t_env *env);
void	reset_room(t_env *env);
char	*create_string(unsigned long nb_ant, char *room);
int		save_info(int set, int new_depth, t_room *o_room, t_env *env);
void	*memalloc_exit(size_t size);
void	clean_conflict(t_env *env);

#endif
