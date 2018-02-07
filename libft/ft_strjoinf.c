/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:40:01 by sbrochar          #+#    #+#             */
/*   Updated: 2018/02/07 16:21:36 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strjoinf(char *s1, char *s2, int which)
{
	char			*ret;
	size_t			size;

	ret = NULL;
	size = 0;
	if (s1)
		size += ft_strlen(s1);
	if (s2)
		size += ft_strlen(s2);
	ret = ft_strnew(size);
	if (ret)
	{
		if (s1)
			ret = ft_strcpy(ret, s1);
		if (s2)
			ret = ft_strcat(ret, s2);
		if (which == 1 && s1)
			ft_strdel(&s1);
		if (which == 2 && s2)
			ft_strdel(&s2);
		return (ret);
	}
	return (NULL);
}
