/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:03:13 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/22 16:54:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	void	*tmp;

	i = 0;
	tmp = (void*)malloc(n);
	if (tmp)
	{
		while (i < n)
		{
			((char*)tmp)[i] = ((char*)src)[i];
			i++;
		}
		i = 0;
		while (i < n)
		{
			((char*)dest)[i] = ((char*)tmp)[i];
			i++;
		}
		free(tmp);
	}
	return (dest);
}
