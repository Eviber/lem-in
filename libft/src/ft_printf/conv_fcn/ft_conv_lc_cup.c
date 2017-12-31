/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_lc_cup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:04:06 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 17:16:33 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_lc_cup(t_ftplst *list, va_list *ap)
{
	int			i;
	wint_t		input;
	int			size;

	i = ft_strlen(list->flag) - 1;
	input = 0;
	list->arg = NULL;
	if (!(list->flag[i] == 'C' || (list->flag[i] == 'c' && \
	list->flag[i - 1] == 'l' && list->flag[i - 2] != 'l')))
		return (NULL);
	input = va_arg(*ap, wint_t);
	size = ft_wcrtomb(list->arg, (wchar_t)input);
	if (size > MB_CUR_MAX)
		return (NULL);
	list->arg = ft_strnew(size + 1);
	size = ft_wcrtomb(list->arg, (wchar_t)input);
	list->arg[size] = '\0';
	if (!list->arg[0])
		list->nullchar++;
	ft_printf_field(list, ft_printf_attribute_zero_char(list));
	return (list->arg);
}
