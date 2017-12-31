/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_switch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:00:05 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 18:36:47 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_switch_spec(t_ftplst *list, va_list *ap)
{
	if (ft_conv_lc_cup(list, ap))
		return ;
	else if (ft_conv_ls_sup(list, ap))
		return ;
	else if (ft_conv_b(list, ap))
		return ;
	else if (ft_conv_percent(list))
		return ;
	else if (list->flag_ok == 1)
		list->arg = ft_conv_not_valid(list);
	else
		return ;
}

void		ft_printf_switch(t_ftplst *list, va_list *ap)
{
	ft_printf_load_struct(list, ap);
	if (list->flag_ok <= 0)
		return ;
	if (ft_conv_c(list, ap))
		return ;
	else if (ft_conv_di(list, ap))
		return ;
	else if (ft_conv_o(list, ap))
		return ;
	else if (ft_conv_u(list, ap))
		return ;
	else if (ft_conv_xp_xup(list, ap))
		return ;
	else if (ft_conv_s(list, ap))
		return ;
	else if (ft_conv_p(list, ap))
		return ;
	else
		ft_printf_switch_spec(list, ap);
}
