/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_clear_flag.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:50:45 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 17:04:47 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_printf_get_attribute(t_ftplst *list)
{
	char	*tmp;

	if ((list->clean_flag = ft_strnew(5)))
	{
		list->index.j = 1;
		list->clean_flag[0] = '%';
		while (ft_isattribute(list->flag[list->index.i]))
			list->index.i++;
		if (list->index.i != 1 && (tmp = ft_strsub(list->flag, 1, \
		(list->index.i - 1))))
		{
			if (ft_strchr(tmp, '#'))
				list->clean_flag[list->index.j++] = '#';
			if (ft_strchr(tmp, '+'))
				list->clean_flag[list->index.j++] = '+';
			else if (ft_strchr(tmp, ' '))
				list->clean_flag[list->index.j++] = ' ';
			if (ft_strchr(tmp, '-'))
				list->clean_flag[list->index.j++] = '-';
			else if (ft_strchr(tmp, '0'))
				list->clean_flag[list->index.j++] = '0';
			ft_strdel(&tmp);
			list->clean_flag[list->index.j] = '\0';
		}
	}
}

static void		ft_switch_clear_flag(t_ftplst *list, va_list *ap)
{
	ft_printf_get_attribute(list);
	ft_printf_search_field(list, ap);
	if (list->flag[list->index.i] == '.')
		ft_printf_search_prec(list, ap);
	if (!ft_printf_search_conv(list))
	{
		list->clean_flag = ft_strjoin_free(list->clean_flag, \
		list->flag + (ft_strlen(list->flag) - 1), 1);
		list->flag_ok = 1;
	}
	else
	{
		list->clean_flag = ft_strjoin_free(list->clean_flag, \
		list->flag + list->index.i, 1);
		if (ft_isalpha(list->clean_flag[ft_strlen(list->clean_flag) - 1]))
			list->flag_ok = -1;
	}
}

void			ft_printf_clear_flag(t_ftplst *list, va_list *ap)
{
	list->index.i = 1;
	if (list->flag[ft_strlen(list->flag) - 1] == '%')
	{
		list->clean_flag = ft_strdup(list->flag);
		list->flag_ok = ((ft_strlen(list->flag) - 1) == 0) ? -1 : 1;
	}
	else if (!list->clean_flag)
		ft_switch_clear_flag(list, ap);
}
