/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_attribute_zero.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:38:08 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 19:59:09 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_printf_attribute_zero(t_ftplst *list)
{
	if (list->zero && !list->minus && list->prec <= 0)
		return ('0');
	return (' ');
}

char	ft_printf_attribute_zero_char(t_ftplst *list)
{
	if (list->zero && !list->minus)
		return ('0');
	return (' ');
}

char	ft_printf_attribute_zero_num(t_ftplst *list)
{
	if (list->zero && !list->minus && list->prec < 0)
		return ('0');
	return (' ');
}
