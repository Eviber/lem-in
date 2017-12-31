/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:30:36 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_o(t_ftplst *list, va_list *ap)
{
	int		i;
	char	c;

	c = ft_printf_attribute_zero(list);
	i = ft_strlen(list->flag) - 1;
	list->sign = 0;
	if (list->flag[i] != 'o' && list->flag[i] != 'O')
		return (NULL);
	if (!(list->arg = ft_printf_lenmod_ui(list->flag, ap, i, 8)))
		return (NULL);
	if (list->prec == 0 && list->arg[0] == '0')
		i = 0;
	if (list->sharp)
		ft_printf_attribute_sharp(list, 'o');
	if (list->prec > -1)
		ft_printf_prec(list);
	if (list->field)
		ft_printf_field(list, c);
	if (i == 0)
		list->arg[(ft_strlen(list->arg) - 1)] = ((ft_strlen(list->arg) - 1) \
		== 0) ? '\0' : ' ';
	if (list->sharp && i == 0)
		ft_printf_attribute_sharp(list, 'o');
	return (list->arg);
}
