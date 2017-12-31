/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:57:35 by vsporer           #+#    #+#             */
/*   Updated: 2017/05/02 15:13:18 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nblen(unsigned long long n, int base)
{
	size_t count;

	count = 1;
	while (n / base != 0)
	{
		n = n / base;
		count++;
	}
	return (count);
}

static void		ft_ulltoa_base_rec(char **str, unsigned long long n, int base)
{
	char digit;

	digit = (n % base) + '0';
	if (digit > '9')
		digit = (digit - '9') + 96;
	if (n / base > 0)
		ft_ulltoa_base_rec(str, n / base, base);
	*str = ft_strncat(*str, &digit, 1);
}

char			*ft_ulltoa_base(unsigned long long n, int base)
{
	char *str;

	if ((str = ft_strnew(ft_nblen(n, base))))
	{
		ft_bzero(str, ft_nblen(n, base) + 1);
		if (str)
		{
			ft_ulltoa_base_rec(&str, n, base);
		}
	}
	return (str);
}
