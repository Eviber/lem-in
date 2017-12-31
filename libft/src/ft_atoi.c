/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:29:51 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/15 14:32:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strlen_nb(char *str, int flag)
{
	int i;

	i = 0;
	if (flag != 0)
		while (str[i] > 47 && str[i] < 58)
			i++;
	else
		while (str[i] != 0)
			i++;
	return (i);
}

static int		ft_pow(int nb, int power)
{
	if (power == 0)
		return (1);
	if (power > 0)
		return (nb * ft_pow(nb, power - 1));
	return (0);
}

static int		ft_atoi_rec(char *str, int flag)
{
	if (((*str < 48 || *str > 57) && *str != 32 && *str != 45 && *str != 43 && \
			(*str < 9 || *str > 13)) || (flag == 1 && (*str < 48 || *str > 57)))
		return (0);
	if (*str == 0)
		return (0);
	if (*str == '-')
		return (-1 * ft_atoi_rec(str + 1, 1));
	if (*str == '+')
		return (ft_atoi_rec(str + 1, 1));
	if (*str > 47 && *str < 58)
	{
		return ((*str - 48) * ft_pow(10, ft_strlen_nb(str, 1) - 1) +\
				ft_atoi_rec(str + 1, 1));
	}
	return (ft_atoi_rec(str + 1, 0));
}

int				ft_atoi(const char *str)
{
	char str1[ft_strlen_nb((char *)str, 0)];

	ft_strcpy(str1, str);
	return (ft_atoi_rec(str1, 0));
}
