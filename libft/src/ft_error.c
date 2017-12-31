/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 14:19:50 by vsporer           #+#    #+#             */
/*   Updated: 2017/12/01 20:03:39 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(int err, char *msg, char mode)
{
	if (err <= 0)
		perror(msg);
	else if (msg)
		ft_putendl_fd(msg, 2);
	if (mode == 'q')
		exit(err);
}
