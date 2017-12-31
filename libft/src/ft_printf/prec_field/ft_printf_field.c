/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_field.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:59:58 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:56:55 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf_get_field(char *flag)
{
	char	*tmp;

	tmp = flag;
	while (!(*tmp >= '1' && *tmp <= '9') && *tmp && *tmp != '.')
		tmp++;
	if (*tmp >= '1' && *tmp <= '9')
		return (ft_atoi(tmp));
	else
		return (0);
}

void		ft_printf_field_di(t_ftplst *list, char c)
{
	char	*tmp;
	int		i;

	if (list->field < 0)
		i = (-list->field - ft_strlen(list->arg));
	else
		i = (list->field - ft_strlen(list->arg));
	if (!*list->arg)
		i = list->field;
	if (!ft_strchr(list->arg, '-') && list->sign && list->minus)
		i--;
	if (!(i <= 0))
	{
		if ((tmp = ft_strnew((size_t)i)))
		{
			while (i)
				tmp[--i] = c;
			if ((list->minus && list->field != 0) || list->field < 0)
				list->arg = ft_strjoin_free(list->arg, tmp, 3);
			else
				list->arg = ft_strjoin_free(tmp, list->arg, 3);
		}
	}
}

static void	ft_apply_field(t_ftplst *list, char *tmp)
{
	if ((list->minus && list->field != 0) || list->field < 0)
	{
		if (!*list->arg)
		{
			if (list->flag[ft_strlen(list->flag) - 1] == 's')
				tmp[ft_strlen(tmp) - 1] = '\0';
			else
				*tmp = *list->arg;
			ft_strdel(&list->arg);
			list->arg = tmp;
		}
		else
			list->arg = ft_strjoin_free(list->arg, tmp, 3);
	}
	else if (!*list->arg)
	{
		tmp[ft_strlen(tmp) - 1] = *list->arg;
		ft_strdel(&list->arg);
		list->arg = tmp;
	}
	else
		list->arg = ft_strjoin_free(tmp, list->arg, 3);
}

void		ft_printf_field(t_ftplst *list, char c)
{
	char	*tmp;
	int		i;

	if (list->field < 0)
		i = (-list->field - ft_strlen(list->arg));
	else
		i = (list->field - ft_strlen(list->arg));
	if (!*list->arg)
		i = list->field;
	if (list->sign && list->minus)
		i--;
	if (list->nullchar == 0 && list->arg[0] == '\0')
		i++;
	if (!(i <= 0))
	{
		if ((tmp = ft_strnew((size_t)i)))
		{
			while (i)
				tmp[--i] = c;
			ft_apply_field(list, tmp);
		}
	}
}
