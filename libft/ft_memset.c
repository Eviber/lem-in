/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 00:09:18 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/22 11:08:40 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void				*ft_memset(void *ptr, int byte, size_t size)
{
	unsigned int	i;
	unsigned char	*cursor;
	unsigned char	value;

	i = 0;
	cursor = (unsigned char*)ptr;
	value = (unsigned char)byte;
	while (i < size)
		cursor[i++] = value;
	return (ptr);
}
