/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 19:47:35 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/29 11:03:37 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s);
	while (i && s[i] != c)
		i--;
	return ((s[i] == c) ? (char *)&s[i] : NULL);
}
