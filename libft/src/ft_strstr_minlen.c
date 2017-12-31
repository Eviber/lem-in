/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_minlen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:18:28 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/15 14:18:29 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr_minlen(const char *haystack, const char *needle, size_t len)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (i < (int)len)
	{
		while (haystack[i + c] == needle[c] && needle[c])
			c++;
		if (!(needle[c]))
			return (&((char*)haystack)[i]);
		c = 0;
		i++;
	}
	if (haystack[i] == needle[c])
		return (&((char*)haystack)[i]);
	return (NULL);
}
