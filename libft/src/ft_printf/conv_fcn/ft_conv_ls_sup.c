/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_ls_sup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:04:15 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 17:18:25 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_conv_ls_sup_wcsrtombs(t_ftplst *list, const wchar_t *input)
{
	int			i;
	size_t		size;

	i = 0;
	size = 0;
	if (!(size = ft_wcsrtombs(list->arg, (wchar_t *)input, list->prec)))
		return (ft_strdup("\0"));
	if (list->prec >= 0 && (size - list->prec) > 0)
		i = list->prec;
	else
		i = size;
	list->arg = ft_strnew(i + 1);
	size = ft_wcsrtombs(list->arg, (wchar_t *)input, i);
	return (list->arg);
}

char		*ft_conv_ls_sup(t_ftplst *list, va_list *ap)
{
	int				i;
	const wchar_t	*input;

	i = ft_strlen(list->flag) - 1;
	list->arg = NULL;
	if (!(list->flag[i] == 'S' || (list->flag[i] == 's' && \
	list->flag[i - 1] == 'l' && list->flag[i - 2] != 'l')))
		return (NULL);
	input = va_arg(*ap, wchar_t *);
	if (!input && (list->prec > 0 || (!list->field && \
	list->prec == -1) || list->field))
		list->arg = ft_strdup("(null)");
	else if (!input || (input && input[0] == '\0'))
		list->arg = ft_strdup("\0");
	else if (input[0] == '\0' && list->space)
		return (ft_strdup(" "));
	else
		list->arg = ft_conv_ls_sup_wcsrtombs(list, input);
	if (list->field)
		ft_printf_field(list, ft_printf_attribute_zero(list));
	return (list->arg);
}
