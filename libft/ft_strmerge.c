/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 13:13:58 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/24 14:07:28 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strmerge(char **str, int space, int size)
{
	char	*res;
	size_t	len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (i < size)
		len += ft_strlen(str[i++]) + space;
	len -= space;
	res = ft_strnew(len);
	i = 0;
	j = 0;
	while (i < size)
	{
		ft_strcat(res, str[i++]);
		while (res[j])
			j++;
		res[j] = (i < size && space) ? ' ' : '\0';
	}
	return (res);
}
