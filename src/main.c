/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourmea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:13:57 by pbourmea          #+#    #+#             */
/*   Updated: 2017/12/22 20:13:59 by pbourmea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cookielem_in.h"
#include <stdio.h>

void	ft_error(unsigned long motif)
{
	if (motif == 1)
		ft_putendl(ERR_ALLOC);
	else if (motif == 2)
		ft_putendl("Error");
	else if (motif == 3)
		ft_putendl("error format input\n");
	exit(-1);
}

int		main(void)
{
	t_map map;

	parser(&map);
	return (0);
}
