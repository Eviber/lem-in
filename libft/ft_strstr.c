/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:13:09 by ygaude            #+#    #+#             */
/*   Updated: 2016/12/01 07:54:11 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char				*ft_strstr(const char *big, const char *small)
{
	char	*ptr;

	ptr = (char *)big;
	while (*ptr || !*small)
	{
		if (!*small || !ft_strncmp(ptr, small, ft_strlen(small)))
			return (ptr);
		ptr++;
	}
	return (NULL);
}
