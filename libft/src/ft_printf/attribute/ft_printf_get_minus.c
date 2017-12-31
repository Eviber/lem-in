/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_minus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:36:48 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/19 13:36:51 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_get_minus(char *flag)
{
	int		i;

	i = 1;
	while (flag[i] == ' ' || flag[i] == '#' || flag[i] == '0' || \
	flag[i] == '-' || flag[i] == '+')
	{
		if (flag[i] == '-')
			return (1);
		i++;
	}
	return (0);
}
