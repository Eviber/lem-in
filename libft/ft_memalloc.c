/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 00:08:59 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/02 18:43:08 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				*ft_memalloc(size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	if (!(ptr = (char *)malloc(size)))
		return (NULL);
	while (ptr && i < size)
		ptr[i++] = 0;
	return ((void *)ptr);
}
