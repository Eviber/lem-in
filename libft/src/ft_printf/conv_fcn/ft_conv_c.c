/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:34 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 17:17:22 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_c(t_ftplst *list, va_list *ap)
{
	int				i;
	unsigned char	input;

	i = ft_strlen(list->flag) - 1;
	input = 0;
	if (list->flag[i] != 'c' || (list->flag[i] == 'c' && \
	list->flag[i - 1] == 'l' && list->flag[i - 2] != 'l'))
		return (NULL);
	input = (unsigned char)va_arg(*ap, int);
	if ((list->arg = (char *)(unsigned char *)ft_strnew(1)))
		if (!(list->arg[0] = input))
			list->nullchar++;
	ft_printf_field(list, (ft_printf_attribute_zero_char(list)));
	return (list->arg);
}
