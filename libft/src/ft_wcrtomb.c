/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcrtomb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:50:40 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/07 15:50:55 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wcrtomb(char *str, wchar_t wc)
{
	if (str)
	{
		if (wc <= 0x7F)
			str[0] = wc;
		else if (wc <= 0x7FF)
		{
			str[0] = (wc >> 6) + 0xC0;
			str[1] = (wc & 0x3F) + 0x80;
		}
		else if (wc <= 0xFFFF)
		{
			str[0] = (wc >> 12) + 0xE0;
			str[1] = ((wc >> 6) & 0x3F) + 0x80;
			str[2] = (wc & 0x3F) + 0x80;
		}
		else if (wc <= 0x10FFFF)
		{
			str[0] = (wc >> 18) + 0xF0;
			str[1] = ((wc >> 12) & 0x3F) + 0x80;
			str[2] = ((wc >> 6) & 0x3F) + 0x80;
			str[3] = ((wc & 0x3F) + 0x80);
		}
	}
	return (ft_wcharlen(wc));
}
