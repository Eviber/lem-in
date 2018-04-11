/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 19:31:17 by sbrochar          #+#    #+#             */
/*   Updated: 2018/02/07 16:20:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strcjoin(char const *s1, char const *s2, char c)
{
	char			*ret;
	size_t			size;

	if (s1 && s2)
	{
		size = ft_strlen(s1);
		ret = ft_strnew(size + 1);
		ret = ft_strcpy(ret, s1);
		ret[size] = c;
		ret = ft_strjoinf(ret, (char *)s2, 1);
		return (ret);
	}
	return (NULL);
}
