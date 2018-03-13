/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 21:12:58 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/16 19:51:49 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

static char		*create_msg(int err)
{
	char	*msg[2];

	msg[0] = NULL;
	msg[1] = "lem_in: ants error";
	if (err >= 0 && err < 2)
		return (msg[err]);
	else
		return (NULL);
}

void			lem_in_error(int err, char mode, t_env *env)
{
	char	*msg;

	msg = create_msg(err);
	del_room_tab(env->rooms);
	if (err <= 0)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, 2);
	if (mode == 'q')
		exit(err);
}
