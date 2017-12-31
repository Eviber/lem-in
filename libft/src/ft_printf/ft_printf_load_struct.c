/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_load_struct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:49:31 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:55:12 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_load_struct(t_ftplst *list, va_list *ap)
{
	ft_printf_clear_flag(list, ap);
	if (list->flag_ok && list->flag_ok != -1)
	{
		list->field = ft_printf_get_field(list->clean_flag);
		list->prec = ft_printf_get_prec(list->clean_flag);
		list->sharp = (ft_strchr(list->clean_flag, '#')) ? (1) : (0);
		list->zero = ft_printf_get_zero(list->clean_flag);
		list->minus = ft_printf_get_minus(list->clean_flag);
		list->space = (ft_strchr(list->clean_flag, ' ')) ? (1) : (0);
		list->sign = (ft_strchr(list->clean_flag, '+')) ? (1) : (0);
	}
}
