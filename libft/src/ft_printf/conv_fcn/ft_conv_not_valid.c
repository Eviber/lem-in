/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_not_valid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:42:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 21:35:17 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_not_valid(t_ftplst *list)
{
	char	c;

	c = list->flag[ft_strlen(list->flag) - 1];
	if ((list->arg = ft_strnew(1)))
		list->arg[0] = c;
	ft_printf_field(list, ft_printf_attribute_zero(list));
	return (list->arg);
}
