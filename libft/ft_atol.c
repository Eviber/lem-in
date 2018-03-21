/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:55:45 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/21 21:58:23 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long				ft_atol(const char *str)
{
	long	ret;
	int		i;
	int		sign;

	i = 0;
	ret = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i] > 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + ((str[i++] - '0') * sign);
	return (ret);
}
