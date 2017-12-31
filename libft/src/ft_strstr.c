/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:18:28 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/15 14:18:29 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (haystack[i])
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
