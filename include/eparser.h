/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eparser.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:52:59 by sbrochar          #+#    #+#             */
/*   Updated: 2018/01/18 21:44:49 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EPARSER_H
# define EPARSER_H

#include <libft.h>

int					parse_antfarm(t_env *antfarm);
int					parse_room(int *start, int *end, t_env *antfarm, char *line);
int					parse_pipe(t_env *antfarm, char *line);
t_room				**add_room(t_room **rooms, int nb_rooms);
t_room				*find_room(t_env *antfarm, char *name);
void				free_antfarm(t_env *antfarm);

#endif
