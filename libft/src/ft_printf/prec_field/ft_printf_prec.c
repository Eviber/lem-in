/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:59:58 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 20:50:46 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_get_prec(char *flag)
{
	if ((flag = ft_strchr(flag, '.')))
		return (ft_atoi(flag + 1));
	else
		return (-1);
}

void	ft_printf_prec(t_ftplst *list)
{
	char	*tmp;
	int		i;
	int		posconv;

	posconv = ft_strlen(list->flag) - 1;
	i = ((ft_strchr(list->flag, '+') && (list->flag[posconv] == 'd' || \
	list->flag[posconv] == 'i'))) ? (ft_strlen(list->arg)) : \
	(ft_strlen(list->arg));
	if (i <= list->prec)
	{
		i = list->prec - i;
		if (*list->arg == '-')
			i++;
		if (list->flag[posconv] == 'p')
			i += 2;
		if ((tmp = ft_strnew(i)))
		{
			while (i > 0)
				tmp[--i] = '0';
			list->arg = (ft_strjoin_free(tmp, list->arg, 3));
		}
	}
}

void	ft_printf_prec_s(t_ftplst *list)
{
	char	*res;

	if ((int)ft_strlen(list->arg) > list->prec && list->prec >= 0)
	{
		res = ft_strnew((size_t)list->prec);
		res = ft_strncpy(res, list->arg, list->prec);
		ft_strdel(&list->arg);
		list->arg = res;
	}
}
