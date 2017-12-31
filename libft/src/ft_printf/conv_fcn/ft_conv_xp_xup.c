/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_xp_xup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:58:10 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_firstchar_zero(t_ftplst *list, int *i)
{
	if (*list->arg == '0')
	{
		list->sharp = 0;
		list->sign = 0;
	}
	if (list->prec == 0 && *list->arg == '0')
		*i = 0;
}

char		*ft_conv_xp_xup(t_ftplst *list, va_list *ap)
{
	int		i;

	i = ft_strlen(list->flag) - 1;
	if (list->flag[i] != 'x' && list->flag[i] != 'X')
		return (NULL);
	if (!(list->arg = ft_printf_lenmod_ui(list->flag, ap, i, 16)))
		return (NULL);
	ft_firstchar_zero(list, &i);
	if (list->prec > -1)
		ft_printf_prec(list);
	if (list->field)
		ft_printf_field(list, ft_printf_attribute_zero_num(list));
	if (list->sharp)
		ft_printf_attribute_sharp(list, 'x');
	if (i == 0)
		list->arg[(ft_strlen(list->arg) - 1)] = ((ft_strlen(list->arg) - 1) \
		== 0) ? '\0' : ' ';
	i = -1;
	while (list->arg[++i] && list->clean_flag[ft_strlen(list->clean_flag) - 1] \
	== 'X')
		list->arg[i] = ft_toupper(list->arg[i]);
	return (list->arg);
}
