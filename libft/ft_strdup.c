/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:42:32 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/28 14:22:03 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char				*ft_strdup(const char *s1)
{
	char	*res;
	int		size;

	size = ft_strlen(s1);
	res = malloc(sizeof(char) * (size + 1));
	if (res)
	{
		ft_memcpy(res, s1, size);
		res[size] = '\0';
	}
	return (res);
}
