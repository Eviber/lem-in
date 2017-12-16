/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eparser.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:52:59 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/16 01:48:21 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EPARSER_H
# define EPARSER_H

#include <libft.h>

int					get_antfarm(t_env *antfarm);
int					parse_room(int *start, int *end, t_env *antfarm, char *line);

#endif
