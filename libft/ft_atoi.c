/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:56:26 by ygaude            #+#    #+#             */
/*   Updated: 2016/12/01 09:52:11 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi(const char *str)
{
	int		res;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]) && str[i] > 0)
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + ((str[i++] - '0') * sign);
	return (res);
}
