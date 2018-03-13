/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memalloc_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 14:06:38 by gcollett          #+#    #+#             */
/*   Updated: 2018/03/12 15:29:50 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*memalloc_exit(size_t size)
{
	void *res;

	res = ft_memalloc(size);
	if (!res)
	{
		write(2, "Malloc error\n", 13);
		exit(1);
	}
	else
		return (res);
}
