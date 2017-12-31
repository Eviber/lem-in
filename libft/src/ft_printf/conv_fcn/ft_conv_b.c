/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 22:26:58 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_b(t_ftplst *list, va_list *ap)
{
	int		i;
	char	c;

	c = ft_printf_attribute_zero(list);
	i = ft_strlen(list->clean_flag) - 1;
	list->sign = 0;
	if (list->clean_flag[i] != 'b' && list->clean_flag[i] != 'B')
		return (NULL);
	if (!(list->arg = ft_printf_lenmod_ui(list->clean_flag, ap, i, 2)))
		return (NULL);
	list->sign = 0;
	if (list->sharp)
		list->arg = ft_strjoin_free("0b", list->arg, 2);
	if (list->field)
		ft_printf_field(list, ' ');
	if (i == 0)
		list->arg[(ft_strlen(list->arg) - 1)] = ((ft_strlen(list->arg) - 1) \
		== 0) ? '\0' : ' ';
	return (list->arg);
}
