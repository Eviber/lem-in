/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:13:42 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/16 15:02:47 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	content_size = (content == NULL) ? 0 : content_size;
	if ((list = (t_list*)malloc(sizeof(t_list))))
	{
		if (content != NULL)
		{
			if (!(list->content = (void*)malloc(content_size)))
			{
				ft_memdel((void**)&list);
				return (NULL);
			}
			ft_memcpy(list->content, content, content_size);
		}
		else
			list->content = NULL;
		list->content_size = content_size;
		list->next = NULL;
	}
	return (list);
}
