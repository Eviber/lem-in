/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_search_conv.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:45:41 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 22:16:46 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_search_conv(t_ftplst *list)
{
	char	*conv;
	char	*flag;

	flag = list->flag;
	list->index.j = 0;
	conv = "%sSpdiouxXcCDOUaAbBeEfFgGHIJkKLmMnNPqQrRtTvVwWyYZ";
	if (ft_islenmod(flag[list->index.i]))
		list->index.i++;
	if ((flag[list->index.i] == 'h' && flag[list->index.i - 1] == 'h') || \
	(flag[list->index.i] == 'l' && flag[list->index.i - 1] == 'l'))
		list->index.i++;
	while (conv[list->index.j] && conv[list->index.j] != flag[list->index.i])
		list->index.j++;
	if (conv[list->index.j])
		list->index.i++;
	if (flag[list->index.i])
		return (list->index.i);
	else
		return (0);
}
