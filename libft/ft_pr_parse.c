/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 04:04:09 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/25 21:00:48 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	**ft_unicconv(char **str, int i, wchar_t c)
{
	if (!(*str = ft_strnew(4)))
		return (NULL);
	(*str)[3] = (i == 3) ? (char)((c & 0x3F) | 0x80) : '\0';
	c = (i == 3) ? c >> 6 : c;
	(*str)[2] = (i > 1) ? (char)((c & 0x3F) | 0x80) : '\0';
	c = (i > 1) ? c >> 6 : c;
	(*str)[1] = (i > 0) ? (char)((c & 0x3F) | 0x80) : '\0';
	(*str)[0] = (i == 0) ? (char)c : (char)((c >> 6) | (0xF0 << (3 - i)));
	return (str);
}

size_t	ft_getsize(t_str chunk)
{
	size_t	size;

	size = 0;
	if (ft_strchr("SpDOUC", chunk.str[chunk.len - 1]))
		size = sizeof(long);
	else if (ft_strnstr(chunk.str, "j", chunk.len))
		size = sizeof(intmax_t);
	else if (ft_strnstr(chunk.str, "z", chunk.len))
		size = sizeof(size_t);
	else if (ft_strnstr(chunk.str, "ll", chunk.len))
		size = sizeof(long long);
	else if (ft_strnstr(chunk.str, "l", chunk.len))
		size = sizeof(long);
	else if (ft_strnstr(chunk.str, "hh", chunk.len))
		size = sizeof(char);
	else if (ft_strnstr(chunk.str, "h", chunk.len))
		size = sizeof(short);
	if ((!size && ft_strchr("diouxX", chunk.str[chunk.len - 1])))
		size = sizeof(int);
	return (size * 8 - (ft_strchr("di", chunk.str[chunk.len - 1]) != NULL));
}

int		ft_parse_wlen(char **str, va_list ap)
{
	int		ret;

	if (**str == '.')
		(*str)++;
	ret = (**str == '*') ? va_arg(ap, int) : 0;
	if (**str == '*')
		(*str)++;
	else
	{
		while (ft_isdigit(**str))
		{
			ret = ret * 10 + (**str - '0');
			(*str)++;
		}
	}
	return (ret);
}

void	ft_parse_flag(t_data *data, va_list ap)
{
	char	*str;
	int		*opt;

	str = data->chunk.str;
	opt = data->option;
	opt[PREC] = -1;
	while (str < data->chunk.str + data->chunk.len)
	{
		opt[HASH] = (*str == '#') ? 1 : opt[HASH];
		opt[PLUS] = (*str == '+') ? 1 : opt[PLUS];
		opt[MINUS] = (*str == '-') ? 1 : opt[MINUS];
		opt[SPACE] = (*str == ' ') ? 1 : opt[SPACE];
		opt[ZERO] = (*str == '0') ? 1 : opt[ZERO];
		if ((*str > '0' && *str <= '9') || *str == '*')
			opt[WIDTH] = ft_parse_wlen(&str, ap);
		else if (*str == '.')
			opt[PREC] = ft_parse_wlen(&str, ap);
		else
			str++;
	}
	opt[PREC] = (opt[PREC] < -1) ? -1 : opt[PREC];
}
