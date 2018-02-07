/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 06:09:38 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/10 03:26:42 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strinsert(char **add, char **str, size_t where, char c)
{
	char	*res;

	if (!(add && *add && str && *str &&
		(res = ft_strnew(ft_strlen(*add) + ft_strlen(*str)))))
		return (NULL);
	ft_strcat(ft_strcat(ft_strncat(res, *str, where), *add), *str + where);
	if (c == 'F' || c == 'B')
		ft_strdel(add);
	if (c == 'S' || c == 'B')
		ft_strdel(str);
	return (res);
}
