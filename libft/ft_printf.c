/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:26:07 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/19 18:02:18 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

int		ft_vasprintf(char **ret, const char *format, va_list ap)
{
	t_str	fmt;
	t_str	res;
	int		error;

	error = 0;
	fmt.str = (char *)format;
	res = ft_loop(fmt, ap, &error);
	*ret = res.str;
	return ((error) ? -1 : res.len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	char	*str;
	int		ret;

	va_start(ap, format);
	ret = ft_vasprintf(&str, format, ap);
	if (ret != -1)
		write(fd, str, ret);
	ft_strdel(&str);
	va_end(ap);
	return (ret);
}

int		ft_asprintf(char **ret, const char *format, ...)
{
	va_list	ap;
	int		bytes;

	va_start(ap, format);
	bytes = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (bytes);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	char	*str;
	int		ret;

	va_start(ap, format);
	ret = ft_vasprintf(&str, format, ap);
	if (ret != -1)
		write(1, str, ret);
	ft_strdel(&str);
	va_end(ap);
	return (ret);
}
