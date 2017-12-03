/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:41:36 by ygaude            #+#    #+#             */
/*   Updated: 2016/12/01 09:45:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char				*ft_strnstr(const char *big, const char *small, size_t len)
{
	char	*ptr;

	ptr = (char *)big;
	if (big && small && !ft_strcmp(big, small))
		return (ptr);
	while (*ptr && len >= ft_strlen(small))
	{
		if (!*small || !ft_strncmp(ptr, small, ft_strlen(small)))
			return (ptr);
		ptr++;
		len--;
	}
	return (NULL);
}
