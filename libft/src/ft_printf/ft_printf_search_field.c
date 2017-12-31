/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_search_field.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:50:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 22:17:57 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_var_field(t_ftplst *list, va_list *ap)
{
	int		arg;

	arg = 0;
	if (ft_isdigit(list->flag[list->index.i + 1]))
	{
		arg = va_arg(*ap, int);
		list->index.i++;
		ft_printf_search_field(list, ap);
	}
	else
	{
		if ((arg = va_arg(*ap, int)) < 0 && \
		(list->clean_flag)[list->index.j - 1] != '-')
			list->clean_flag = ft_strjoin_free(list->clean_flag, \
			ft_itoa(arg), 3);
		else if (arg < 0)
			list->clean_flag = ft_strjoin_free(list->clean_flag, \
			ft_itoa((-arg)), 3);
		else
			list->clean_flag = ft_strjoin_free(list->clean_flag, \
			ft_itoa(arg), 3);
		list->index.i++;
	}
}

void		ft_printf_search_field(t_ftplst *list, va_list *ap)
{
	if (list->flag[list->index.i] == '*')
		ft_var_field(list, ap);
	else if (ft_isdigit(list->flag[list->index.i]))
	{
		while (ft_isdigit(list->flag[list->index.i]))
			list->index.i++;
		if (list->flag[list->index.i] == '*')
			ft_printf_search_field(list, ap);
		else
		{
			list->clean_flag = ft_strjoin_free(list->clean_flag, \
			ft_itoa(ft_printf_get_field(list->flag)), 3);
		}
	}
}
