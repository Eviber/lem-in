/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:57:35 by vsporer           #+#    #+#             */
/*   Updated: 2017/05/02 14:24:51 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nblen(int n)
{
	size_t count;

	count = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n / 10 != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void		ft_itoa_rec(char **str, int n)
{
	char digit;

	digit = (n % 10) + 48;
	if (n / 10 > 0)
		ft_itoa_rec(str, n / 10);
	*str = ft_strncat(*str, &digit, 1);
}

char			*ft_itoa(int n)
{
	char *str;

	if ((str = ft_strnew(ft_nblen(n))))
	{
		ft_bzero(str, ft_nblen(n) + 1);
		if (str)
		{
			if (n < 0)
			{
				if (n == -2147483648)
				{
					ft_strcpy(str, "-2147483648");
					return (str);
				}
				n = -n;
				str = ft_strcat(str, "-");
			}
			ft_itoa_rec(&str, n);
		}
	}
	return (str);
}
