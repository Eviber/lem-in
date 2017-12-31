/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:59:42 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 19:05:11 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_search_percent(const char *format)
{
	size_t	i;

	i = 0;
	while (format[i] && format[i] != '%')
		i++;
	return (i);
}

static int		ft_search_conv(char c)
{
	int		i;
	char	*conv;

	conv = "sSpdDioOuUxXcCaAbBeEfFgGIJJkKLmMnNPqQrRtTvVwWyYZ%";
	i = 0;
	while (conv[i] && conv[i] != c)
		i++;
	if (conv[i])
		return (1);
	else
		return (0);
}

t_ftplst		*ft_get_flag(const char *format)
{
	int			i;
	int			end;
	t_ftplst	*list;

	list = NULL;
	while (*(format += ft_search_percent(format)))
	{
		end = *format == '%' ? 1 : 0;
		if (*format)
			i = 0;
		while (format[end] && !i)
		{
			i = ft_search_conv(format[end]);
			if (i)
				ft_ftplstaddback(&list, ft_ftplstnew(ft_strsub(format, 0, \
				(end + 1))));
			end++;
		}
		format += end;
	}
	return (list);
}
