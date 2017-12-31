/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 21:11:08 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/12 16:41:54 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtabadd(char ***tab, char *str)
{
	int		len;
	char	**new;

	if (!str)
		return (0);
	len = ft_strtablen(*tab);
	len++;
	if ((new = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		len--;
		new[len + 1] = NULL;
		new[len] = str;
		while (*tab && --len >= 0)
			new[len] = (*tab)[len];
		ft_memdel((void**)tab);
		*tab = new;
		return (0);
	}
	else
		return (1);
}
