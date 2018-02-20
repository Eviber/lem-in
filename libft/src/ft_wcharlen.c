/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 18:50:13 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/20 18:50:16 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

int		ft_wcharlen(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	else if (wc <= 0x7FF)
		return (2);
	else if (wc <= 0x7FFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	else
		return (-1);
}
