/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <gcollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 20:15:21 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/12 13:46:19 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "visu_lem_in.h"
#include "solver.h"

char		*create_string(unsigned long nb_ant, char *room)
{
	char	*res;
	char	*char_ant;
	int		i;
	int		j;

	i = -1;
	j = 0;
	char_ant = ft_ulltoa_base(nb_ant, 10);
	res = memalloc_exit(5 + ft_strlen(room) + ft_strlen(char_ant));
	res[0] = 'L';
	while (char_ant[++i])
		res[++j] = char_ant[i];
	res[++j] = '-';
	i = -1;
	while (room[++i])
		res[++j] = room[i];
	ft_memdel((void**)&char_ant);
	return (res);
}
