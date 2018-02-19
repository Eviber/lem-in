/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_strtab_except.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:43:39 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/02 16:00:08 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

void	del_strtab_except(char ***tab, int index)
{
	int		i;

	i = -1;
	while (*tab && (*tab)[++i])
		if (i != index)
			ft_strdel(&((*tab)[i]));
	ft_memdel((void**)tab);
}
