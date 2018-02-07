/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 05:38:27 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/28 12:36:59 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*psrc;
	unsigned char	*pdst;
	size_t			i;

	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	i = -1;
	if (dst > src && dst < sizeof(char) * len + src)
	{
		while (len--)
			pdst[len] = psrc[len];
	}
	else
		while (++i < len)
			pdst[i] = psrc[i];
	return (dst);
}
