/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:58:39 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:30:06 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_apply_neg(t_ftplst *list, char *tmp)
{
	if (*list->arg == ' ')
	{
		*tmp = *(tmp - 1);
		tmp = list->arg;
		while (*(tmp + 1) == ' ')
			tmp++;
		if (*tmp != '0' && *(tmp + 1) == '0')
			*(tmp + 1) = '-';
		else
			*tmp = '-';
	}
	else if (*list->arg == '0')
	{
		*tmp = *(tmp - 1);
		tmp = list->arg;
		*tmp = '-';
	}
}

static char	*ft_printf_is_neg(t_ftplst *list)
{
	char	*tmp;

	if (!(tmp = ft_strchr(list->arg, '-')))
		return (list->arg);
	if ((list->arg - tmp) && ((list->zero && list->prec < 0) \
	|| list->prec >= list->field))
	{
		*tmp = *(tmp - 1);
		tmp = list->arg;
		if ((int)ft_strlen(list->arg) < list->prec && list->prec >= list->field)
			return (ft_strjoin_free("-", list->arg, 2));
		else if ((int)ft_strlen(list->arg) < list->field && list->field > \
		list->prec)
			return (ft_strjoin_free("-", list->arg, 2));
		*list->arg = '-';
	}
	else
		ft_apply_neg(list, tmp);
	return (list->arg);
}

char		*ft_conv_di(t_ftplst *list, va_list *ap)
{
	int		i;
	char	c;

	c = ft_printf_attribute_zero_num(list);
	i = ft_strlen(list->flag) - 1;
	if (list->flag[i] != 'd' && list->flag[i] != 'i' && \
	list->flag[i] != 'D')
		return (NULL);
	if (!(list->arg = ft_printf_lenmod_i(list->flag, ap, i)))
		return (NULL);
	if (!list->arg[0])
		list->nullchar++;
	if (ft_strlen(list->arg) == 1 && *list->arg == '0' && list->prec == 0)
		*list->arg = '\0';
	if (list->prec > -1)
		ft_printf_prec(list);
	if (list->field)
		ft_printf_field_di(list, c);
	if (list->space && !list->sign)
		list->arg = ft_printf_attribute_space(list->arg);
	else if (list->sign)
		ft_printf_attribute_sign_di(list);
	list->arg = ft_printf_is_neg(list);
	return (list->arg);
}
