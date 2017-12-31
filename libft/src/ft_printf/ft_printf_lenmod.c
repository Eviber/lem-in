/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lenmod.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 11:00:02 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/05 16:26:53 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_lenmod_i(char *flag, va_list *ap, int i)
{
	long long	input;
	char		*res;
	char		*tmp;
	int			neg;

	if (flag[i] == 'D')
		input = (long long)va_arg(*ap, long);
	else if (flag[i - 1] == 'h' && flag[i - 2] == 'h')
		input = (long long)((char)va_arg(*ap, int));
	else if (flag[i - 1] == 'h')
		input = (long long)((short)va_arg(*ap, int));
	else if (flag[i - 1] == 'l' && flag[i - 2] == 'l')
		input = va_arg(*ap, long long);
	else if (flag[i - 1] == 'l' || flag[i] == 'D')
		input = (long long)va_arg(*ap, long);
	else if (flag[i - 1] == 'j')
		input = va_arg(*ap, long long);
	else if (flag[i - 1] == 'z')
		input = (long long)va_arg(*ap, size_t);
	else
		input = (long long)va_arg(*ap, int);
	neg = (input < 0) ? (-1) : (1);
	tmp = ft_ulltoa_base((unsigned long long)(input * neg), 10);
	return (res = (neg < 0) ? (ft_strjoin_free("-", tmp, 2)) : (tmp));
}

char	*ft_printf_lenmod_ui(char *flag, va_list *ap, int i, int base)
{
	unsigned long long	input;

	if (flag[i] == 'O' || flag[i] == 'U')
		input = (unsigned long long)va_arg(*ap, unsigned long);
	else if (flag[i] == 'p')
		input = (unsigned long long)va_arg(*ap, void *);
	else if (flag[i - 1] == 'h' && flag[i - 2] == 'h')
		input = (unsigned long long)((unsigned char)va_arg(*ap, unsigned int));
	else if (flag[i - 1] == 'h')
		input = (unsigned long long)((unsigned short)va_arg(*ap, unsigned int));
	else if (flag[i - 1] == 'l' && flag[i - 2] == 'l')
		input = va_arg(*ap, unsigned long long);
	else if (flag[i - 1] == 'l' || flag[i] == 'O' || flag[i] == 'U')
		input = (unsigned long long)va_arg(*ap, unsigned long);
	else if (flag[i - 1] == 'j')
		input = va_arg(*ap, unsigned long long);
	else if (flag[i - 1] == 'z')
		input = (unsigned long long)va_arg(*ap, size_t);
	else
		input = (unsigned long long)va_arg(*ap, unsigned int);
	return (ft_ulltoa_base(input, base));
}
