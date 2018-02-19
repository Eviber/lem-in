/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 19:28:40 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/16 19:57:23 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

void	add_pipe(t_room ***pipe, t_room *to, t_env *env)
{
	int		i;
	t_room	**new;

	i = 0;
	while (*pipe && (*pipe)[i])
		i++;
	i++;
	if (!(new = (t_room**)malloc(sizeof(t_room*) * (i + 1))))
		lem_in_error(DEFAULT, 'q', env);
	i--;
	new[i] = to;
	new[i + 1] = NULL;
	while (--i >= 0)
		new[i] = (*pipe)[i];
	ft_memdel((void**)pipe);
	*pipe = new;
}
