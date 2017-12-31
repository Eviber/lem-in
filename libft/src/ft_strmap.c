/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:58:57 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/24 16:59:00 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dest;
	size_t	i;

	if (s)
	{
		if ((dest = ft_strnew(ft_strlen(s))))
		{
			i = 0;
			while (s[i])
			{
				dest[i] = f(s[i]);
				i++;
			}
		}
		return (dest);
	}
	return (NULL);
}
