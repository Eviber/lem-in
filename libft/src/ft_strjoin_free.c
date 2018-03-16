/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:58:54 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/16 17:42:33 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int i)
{
	char			*dest;

	dest = ft_strjoin(s1, s2);
	if (i == 1 || i == 3)
		ft_strdel(&s1);
	if (i == 2 || i == 3)
		ft_strdel(&s2);
	return (dest);
}
