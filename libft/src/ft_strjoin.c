/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:58:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/16 17:22:42 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	size;

	size = 0;
	dest = NULL;
	if (s1)
		size = ft_strlen(s1);
	if (s2)
		size += ft_strlen(s2);
	if (size > 0 && (dest = ft_strnew(size)))
	{
		if (s1)
			ft_strcpy(dest, s1);
		if (s1 && s2)
			ft_strcat(dest, s2);
		else if (s2)
			ft_strcpy(dest, s2);
		if (!s1 && !s2)
			dest = NULL;
	}
	return (dest);
}
