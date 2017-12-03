/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 03:18:08 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/10 03:18:58 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_imaxtoa(intmax_t n, unsigned int base)
{
	char	*str;
	char	*tmp;

	tmp = "-";
	str = ft_uimaxtoa((uintmax_t)((n < 0) ? -n : n), base);
	return ((n < 0) ? ft_strappend(&tmp, &str, 'S') : str);
}
