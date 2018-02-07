/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 18:09:19 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/25 21:00:35 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

t_str	ft_chunkappend(t_str s1, t_str s2, char c)
{
	t_str	res;

	res.len = s1.len + s2.len;
	if (s1.str && s2.str && s1.len + s2.len)
		res.str = ft_memjoin(s1.str, s1.len, s2.str, s2.len);
	else if (s1.str && s1.len)
		res.str = ft_memdup(s1.str, s1.len);
	else if (s2.str && s2.len)
		res.str = ft_memdup(s2.str, s2.len);
	else
		res.str = ft_memalloc(1);
	if (c == 'F' || c == 'B')
		ft_memdel((void **)&(s1.str));
	if (c == 'S' || c == 'B')
		ft_memdel((void **)&(s2.str));
	return (res);
}

t_str	ft_domagic(t_data data, va_list ap, int *error)
{
	t_str	res;
	char	spec;

	spec = data.chunk.str[data.chunk.len - 1];
	ft_memset(&res, 0, sizeof(res));
	ft_parse_flag(&data, ap);
	if (ft_strchr(SPECIFIER, spec))
	{
		res = ft_convert(data, ap, ft_getsize(data.chunk), data.option[PREC]);
		if (res.str)
			res = ft_apply(res, data.option, spec);
	}
	else
	{
		res.str = ft_strnew(1);
		res.str[0] = spec;
		res.len = 1;
		res = ft_apply(res, data.option, spec);
	}
	*error = (*error || res.str == NULL);
	return (res);
}

t_data	ft_loop_check(int check, t_data data, int *error, va_list ap)
{
	if (check)
		data.res = ft_chunkappend(data.res, ft_domagic(data, ap, error), 'B');
	else
	{
		data.chunk.len--;
		data.res = ft_chunkappend(data.res, data.chunk, 'F');
	}
	data.chunk.len = 0;
	return (data);
}

t_str	ft_loop(t_str fmt, va_list ap, int *error)
{
	t_data	data;
	int		inflag;
	int		check;
	char	c;

	ft_memset(&data, 0, sizeof(data));
	fmt.len = (size_t)-1;
	inflag = 0;
	data.chunk.str = fmt.str;
	while ((c = fmt.str[++fmt.len]))
	{
		data.chunk.len = fmt.str + fmt.len - data.chunk.str + 1;
		check = (inflag && !ft_strchr(FLAG, c));
		if (check || (!check && (c == '%')))
		{
			data = ft_loop_check(check, data, error, ap);
			inflag = !check;
			data.chunk.str = fmt.str + fmt.len + check;
		}
	}
	if (!inflag && !(*error))
		data.res = ft_chunkappend(data.res, data.chunk, 'F');
	return (data.res);
}
