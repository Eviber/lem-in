/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_strtab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:43:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/16 19:52:52 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"

void	del_strtab(char ***tab)
{
	int		i;

	i = -1;
	while (*tab && (*tab)[++i])
		ft_strdel(&((*tab)[i]));
	ft_memdel((void**)tab);
}
