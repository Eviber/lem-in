/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 16:56:20 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/10 03:27:56 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_memjoin(void *p1, size_t l1, void *p2, size_t l2)
{
	char	*res;

	if (!p1 || !p2 || !(l1 + l2) || !(res = (char *)ft_memalloc(l1 + l2)))
		return (NULL);
	ft_memcpy(res, p1, l1);
	ft_memcpy(res + l1, p2, l2);
	return (res);
}
