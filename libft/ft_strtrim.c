/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:10:12 by ygaude            #+#    #+#             */
/*   Updated: 2016/12/01 10:18:21 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			trimspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char				*ft_strtrim(const char *s)
{
	unsigned int	start;
	unsigned int	i;
	size_t			len;
	char			*res;

	i = 0;
	if (!s)
		return (NULL);
	if (!s[i])
		return (ft_strdup(""));
	while (trimspace(s[i]))
		i++;
	start = i;
	i = ft_strlen(s) - 1;
	while (i > start && trimspace(s[i]))
		i--;
	if (i < start)
		return (ft_strdup(""));
	i++;
	len = i - start;
	res = ft_strsub(s, start, len);
	return (res);
}
