/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tolst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/20 14:16:19 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 18:40:11 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_printf_skip_nullchar(char *str, int nullchar)
{
	int		i;

	i = 0;
	while (str[i] || nullchar)
	{
		if (str[i] == '\0' && nullchar)
			nullchar--;
		i++;
	}
	return (i);
}

void		ft_printf_tolst(t_ftplst *list, va_list *ap)
{
	size_t	len;

	while (list && list->flag)
	{
		ft_printf_switch(list, ap);
		if (list->flag_ok <= 0 && !list->arg)
			list->arg = ft_strdup(list->clean_flag);
		len = ft_printf_skip_nullchar(list->arg, list->nullchar);
		list->size = len;
		list = list->next;
	}
}
