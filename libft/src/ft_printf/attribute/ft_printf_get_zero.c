/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_zero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:38:58 by vsporer           #+#    #+#             */
/*   Updated: 2017/08/19 13:39:00 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_get_zero(char *flag)
{
	int		i;

	i = 1;
	while (flag[i] == ' ' || flag[i] == '#' || flag[i] == '0' || \
	flag[i] == '-' || flag[i] == '+')
	{
		if (flag[i] == '0')
			return (1);
		i++;
	}
	return (0);
}
