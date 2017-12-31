/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_attribute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:43:19 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 22:22:31 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_printf_attribute_sign_di(t_ftplst *list)
{
	int		i;

	i = 0;
	if (list->arg)
	{
		if (!ft_strchr(list->arg, '-'))
		{
			while (list->arg[i] == ' ')
				i++;
			if (i && list->arg[i - 1] == ' ')
				list->arg[i - 1] = '+';
			else if (list->arg[i] == '0' && \
			(list->field - ft_strlen(list->arg)) <= 0 && list->arg[i + 1])
				list->arg[i] = '+';
			else
				list->arg = ft_strjoin_free("+", list->arg, 2);
		}
	}
}

void		ft_printf_attribute_sign(t_ftplst *list)
{
	int		i;

	i = 0;
	if (list->arg)
	{
		if (!ft_strchr(list->arg, '-'))
		{
			while (list->arg[i] == ' ')
				i++;
			if (i && list->arg[i - 1] == ' ')
				list->arg[i - 1] = '+';
			else if (list->arg[i] == '0' && \
			(list->field - list->prec) > 0 && list->arg[i + 1])
				list->arg[i] = '+';
			else
				list->arg = ft_strjoin_free("+", list->arg, 2);
		}
	}
}

static void	ft_apply_sharp(t_ftplst *list, int i)
{
	if (!i)
	{
		if (list->arg[0] == '0' && list->arg[1] == '0' && \
		((list->field - list->prec) >= 2 || \
		list->clean_flag[ft_strlen(list->clean_flag) - 1] == 'p'))
			list->arg[1] = 'x';
		else if (list->arg[0] == '0' && list->arg[1] != ' ' && \
		(list->field > list->prec || \
		list->clean_flag[ft_strlen(list->clean_flag) - 1] == 'p'))
		{
			list->arg[0] = 'x';
			list->arg = ft_strjoin_free("0", list->arg, 2);
		}
		else
			list->arg = ft_strjoin_free("0x", list->arg, 2);
	}
	else if (i == 1)
	{
		list->arg[0] = 'x';
		list->arg = ft_strjoin_free("0", list->arg, 2);
	}
	else
		ft_memcpy(&(list->arg[i - 2]), "0x", 2);
}

void		ft_printf_attribute_sharp(t_ftplst *list, char c)
{
	int		i;

	i = 0;
	if (list->arg)
	{
		if (c == 'o' && list->arg[0] != '0')
			list->arg = ft_strjoin_free("0", list->arg, 2);
		else if (c == 'x' || c == 'X')
		{
			if (!(list->arg[0] == '0' && list->arg[1] == '\0'))
			{
				while (list->arg[i] == ' ')
					i++;
				ft_apply_sharp(list, i);
				i = ft_strlen(list->arg) - 1;
				if (ft_strchr(list->clean_flag, '-') && list->arg[i] == ' ' && \
				list->arg[i - 1] == ' ')
					list->arg[i - 1] = '\0';
				else if (ft_strchr(list->clean_flag, '-') && list->arg[i] \
				== ' ')
					list->arg[i] = '\0';
			}
		}
	}
}

char		*ft_printf_attribute_space(char *str)
{
	if (str && !ft_strchr(str, '-'))
	{
		if (str[0] == '\0')
			return (ft_strdup(" \0"));
		if (*str == '0' && str[1] == '0')
			*str = ' ';
		else if (*str != ' ')
			return (ft_strjoin_free(" ", str, 2));
		else
			return (str);
	}
	return (str);
}
