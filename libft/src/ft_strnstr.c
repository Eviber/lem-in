/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:18:05 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/15 14:18:08 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int i;
	unsigned int c;

	i = 0;
	c = 0;
	while (big[i + c] && i < len)
	{
		while (big[i + c] == little[c] && little[c] && (i + c) < len)
			c++;
		if (little[c] == 0)
			return (&((char*)big)[i]);
		c = 0;
		i++;
	}
	if (i >= len)
		return (NULL);
	if (big[i] == little[c])
		return (&((char*)big)[i]);
	return (NULL);
}
