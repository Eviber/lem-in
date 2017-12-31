/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:59:07 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/24 16:59:10 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(unsigned long size)
{
	char *str;

	if ((str = (char*)ft_memalloc(size + 1)))
	{
		str[size] = 0;
		return (str);
	}
	return (NULL);
}
