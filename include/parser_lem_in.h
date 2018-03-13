/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem_in.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 16:24:46 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/02 16:00:39 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_LEM_IN_H
# define PARSER_LEM_IN_H

# include "libft.h"
# define DEFAULT 0
# define ANTS 1

/*
** Base
*/
void			lem_in_error(int err, char mode, t_env *env);
/*
** Tools
*/
void			del_room_tab(t_room **room);
void			del_strtab(char ***tab);
void			del_strtab_except(char ***tab, int index);
t_room			*search_room(char *name, t_room **room);
/*
** Parser
*/
int				check_in(char *line, t_env *env);
char			**read_map(t_env *env);
void			check_map(t_env *env);
void			add_pipe(t_room ***pipe, t_room *to, t_env *env);
t_room			*new_room(char *name, int x, int y, t_env *env);
/*
** Solver
*/
void			get_path(t_env *env);
void			release_ants(t_env *env);

#endif
