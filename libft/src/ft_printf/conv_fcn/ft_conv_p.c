/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:44:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:41:23 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_len_zero(t_ftplst *list)
{
	list->arg[ft_strlen(list->arg) - 1] = '\0';
	if ((list->field - ft_strlen(list->arg)) > 0)
		list->arg = ft_strjoin_free(" ", list->arg, 2);
	return (list->arg);
}

char		*ft_conv_p(t_ftplst *list, va_list *ap)
{
	int		i;
	int		posconv;

	i = 1;
	posconv = ft_strlen(list->clean_flag) - 1;
	if (list->clean_flag[posconv] != 'p')
		return (NULL);
	if (!(list->arg = ft_printf_lenmod_ui(list->clean_flag, ap, posconv, 16)))
		return (NULL);
	if (list->prec == 0 && list->arg[0] == '0')
		i = 0;
	if (list->prec > -1)
		ft_printf_prec(list);
	if (list->field)
		ft_printf_field(list, ft_printf_attribute_zero(list));
	ft_printf_attribute_sharp(list, 'x');
	if (i == 0)
		list->arg = ft_len_zero(list);
	if (list->arg[0] == '\0' || (list->arg[0] == '0' && list->arg[1] == '\0'))
		list->arg = ft_strjoin_free("0x", list->arg, 2);
	return (list->arg);
}
