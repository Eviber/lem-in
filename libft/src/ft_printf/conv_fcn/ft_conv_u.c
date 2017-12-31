/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:30:47 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_u(t_ftplst *list, va_list *ap)
{
	int		i;
	char	c;

	c = ft_printf_attribute_zero(list);
	i = ft_strlen(list->flag) - 1;
	if (list->flag[i] != 'u' && list->flag[i] != 'U')
		return (NULL);
	if (!(list->arg = ft_printf_lenmod_ui(list->flag, ap, i, 10)))
		return (NULL);
	if (list->prec > -1)
		ft_printf_prec(list);
	if (list->field)
		ft_printf_field(list, c);
	if (list->arg[0] == '0' && list->arg[1] == '\0' && list->prec == 0)
		list->arg[0] = '\0';
	return (list->arg);
}
