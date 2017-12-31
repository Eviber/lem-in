/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_search_prec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:49:35 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 22:17:08 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_var_prec(t_ftplst *list, va_list *ap)
{
	int		arg;

	arg = 0;
	arg = va_arg(*ap, int);
	if (arg < 0)
		list->index.i++;
	else if (arg == 0)
		list->clean_flag = ft_strjoin_free(list->clean_flag, ".0", 1);
	else
		list->clean_flag = ft_strjoin_free(list->clean_flag, \
		ft_strjoin_free(".", ft_itoa(arg), 2), 3);
	list->index.i++;
}

void		ft_printf_search_prec(t_ftplst *list, va_list *ap)
{
	list->index.i++;
	if (list->flag[list->index.i] == '*')
		ft_var_prec(list, ap);
	else if (ft_isdigit(list->flag[list->index.i]))
	{
		while (ft_isdigit(list->flag[list->index.i]))
			list->index.i++;
		list->clean_flag = ft_strjoin_free(list->clean_flag, \
		ft_strjoin_free(".", ft_itoa(ft_printf_get_prec(list->flag)), 2), 3);
	}
	else
		list->clean_flag = ft_strjoin_free(list->clean_flag, ".0", 1);
}
