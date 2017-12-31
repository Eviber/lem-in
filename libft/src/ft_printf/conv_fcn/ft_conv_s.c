/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:51 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 17:18:42 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_s(t_ftplst *list, va_list *ap)
{
	int			i;
	const char	*input;

	i = ft_strlen(list->flag) - 1;
	input = NULL;
	if (list->flag[i] != 's' || (list->flag[i] == 's' && \
	list->flag[i - 1] == 'l'))
		return (NULL);
	input = va_arg(*ap, char *);
	if (!input && (list->prec > 0 || (!list->field && \
	list->prec == -1) || list->field))
		input = "(null)";
	else if (!input)
		input = "\0";
	list->arg = ft_strdup(input);
	if (list->prec != -1)
		ft_printf_prec_s(list);
	if (list->field)
		ft_printf_field(list, ft_printf_attribute_zero(list));
	return (list->arg);
}
