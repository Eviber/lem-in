/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prconvert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 20:05:45 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/25 21:00:14 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

t_str	ft_unic(wchar_t unicstr[], int justonce, int prec, char **str)
{
	int		i;
	t_str	res;
	wchar_t	c;

	res.str = ft_strnew(0);
	while (*unicstr || justonce)
	{
		c = *unicstr;
		i = (c >= 0x80) + (c >= 0x800) + (c >= 0x10000) + (c >= 0x110000);
		if (i + 1 > MB_CUR_MAX)
		{
			ft_strdel(&(res.str));
			return (res);
		}
		if (prec != -1 && i + 1 > prec)
			break ;
		prec -= (prec == -1) ? 0 : i + 1;
		res.str = ft_strappend(&(res.str), ft_unicconv(str, i, c), 'B');
		if (justonce)
			break ;
		unicstr++;
	}
	res.len = (justonce) ? i + 1 : ft_strlen(res.str);
	return (res);
}

t_str	ft_getstring(char spec, va_list ap, size_t size, int prec)
{
	t_str	res;
	wchar_t	tmp;
	char	*str;

	if (spec == 'c' && size < sizeof(long) * 8 && (res.len = 1))
		res.str = ft_memset(ft_strnew(1), (char)va_arg(ap, int), 1);
	else if (spec == 'c' || spec == 'C')
	{
		tmp = va_arg(ap, wchar_t);
		res = ft_unic(&tmp, 1, prec, &str);
	}
	else
	{
		res.str = (spec == 's' && size < sizeof(long) * 8) ?
			(char *)va_arg(ap, char *) : (char *)va_arg(ap, wchar_t *);
		if (!res.str)
			res.str = ft_strdup("(null)");
		else if (spec == 's' && size < sizeof(long) * 8)
			res.str = ft_strdup(res.str);
		else
			res = ft_unic((wchar_t *)res.str, 0, prec, &str);
		res.len = (res.str) ? ft_strlen(res.str) : 0;
	}
	return (res);
}

char	*ft_convert_integer(uintmax_t n, char specifier)
{
	if (specifier == 'b')
		return (ft_uimaxtoa(n, 2));
	if (ft_strchr("uU", specifier))
		return (ft_uimaxtoa(n, 10));
	else if (ft_strchr("pxX", specifier))
		return (ft_uimaxtoa(n, 16));
	else if (ft_strchr("oO", specifier))
		return (ft_uimaxtoa(n, 8));
	else
		return (ft_imaxtoa((intmax_t)n, 10));
}

t_str	ft_getint(char c, va_list ap, size_t size)
{
	t_str	res;

	if (ft_strchr("dDi", c) && size <= sizeof(char) * 8)
		res.str = ft_convert_integer((char)va_arg(ap, int), c);
	else if (ft_strchr("dDi", c) && size <= sizeof(short) * 8)
		res.str = ft_convert_integer((short)va_arg(ap, int), c);
	else if (ft_strchr("dDi", c) && size <= sizeof(int) * 8)
		res.str = ft_convert_integer((int)va_arg(ap, int), c);
	else if (ft_strchr("dDi", c))
		res.str = ft_convert_integer(va_arg(ap, intmax_t), c);
	else if (size <= sizeof(char) * 8)
		res.str = ft_convert_integer((unsigned char)va_arg(ap, int), c);
	else if (size <= sizeof(short) * 8)
		res.str = ft_convert_integer((unsigned short)va_arg(ap, int), c);
	else if (size <= sizeof(int) * 8)
		res.str = ft_convert_integer((unsigned int)va_arg(ap, int), c);
	else
		res.str = ft_convert_integer(va_arg(ap, intmax_t), c);
	res.len = ft_strlen(res.str);
	return (res);
}

t_str	ft_convert(t_data data, va_list ap, size_t size, int prec)
{
	t_str		res;

	if (ft_strchr("sScC", data.chunk.str[data.chunk.len - 1]))
		res = ft_getstring(data.chunk.str[data.chunk.len - 1], ap, size, prec);
	else
		res = ft_getint(data.chunk.str[data.chunk.len - 1], ap, size);
	return (res);
}
