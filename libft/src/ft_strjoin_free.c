/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:58:54 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/24 16:58:57 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char			*dest;
	unsigned int	size;

	size = (s1) ? ft_strlen(s1) : 0;
	size = (s2) ? ft_strlen(s2) : 0;
	if (s1 && s2)
		size = ft_strlen(s1) + ft_strlen(s2);
	if ((dest = ft_strnew(size)))
	{
		if (s1)
			ft_strcpy(dest, s1);
		if (s1 && s2)
			ft_strcat(dest, s2);
		else if (s2)
			ft_strcpy(dest, s2);
		if (!s1 && !s2)
			dest = NULL;
		if (i == 1 || i == 3)
			ft_strdel(&s1);
		if (i == 2 || i == 3)
			ft_strdel(&s2);
	}
	return (dest);
}
