/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 16:07:10 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/09 06:32:47 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char				*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*res;

	if (!s || !(res = ft_strnew(len)))
		return (NULL);
	return (ft_strncpy(res, s + start, len));
}
