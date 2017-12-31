/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:42:51 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 19:09:40 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_conv_percent(t_ftplst *list)
{
	int		i;

	i = ft_strlen(list->clean_flag) - 1;
	list->arg = NULL;
	if (i == 0 || list->clean_flag[i] != '%')
		return (NULL);
	if (!(list->arg = ft_strdup("%")))
		return (NULL);
	ft_printf_field(list, ft_printf_attribute_zero_char(list));
	return (list->arg);
}
