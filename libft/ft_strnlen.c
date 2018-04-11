/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:08:08 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/28 14:24:36 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t				ft_strnlen(char *str, size_t size)
{
	size_t	res;

	res = 0;
	while (res < size && str[res])
		res++;
	return (res);
}
