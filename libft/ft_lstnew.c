/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 10:20:40 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/30 17:58:56 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list				*ft_lstnew(const void *content, size_t content_size)
{
	t_list		*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	if (!content)
	{
		res->content_size = 0;
		res->content = NULL;
	}
	else if ((res->content = malloc(content_size)))
	{
		ft_memcpy(res->content, content, content_size);
		res->content_size = content_size;
	}
	res->next = NULL;
	return (res);
}
