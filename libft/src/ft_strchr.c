/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:15:27 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/15 14:42:47 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	tmp;

	tmp = (char)c;
	while (*s)
	{
		if (*s == tmp)
			return ((char *)s);
		s++;
	}
	if (*s == tmp)
		return ((char *)s);
	return (NULL);
}
