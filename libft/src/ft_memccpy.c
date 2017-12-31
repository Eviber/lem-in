/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 10:59:26 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/18 11:21:48 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char*)src)[i] == (unsigned char)c)
		{
			((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
			return ((void*)&((unsigned char*)dest)[i + 1]);
		}
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return (NULL);
}
