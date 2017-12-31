/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:12:30 by vsporer           #+#    #+#             */
/*   Updated: 2016/11/17 15:06:17 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*returnable;
	t_list	*new_lst;

	if (lst)
	{
		if ((new_lst = f(lst)))
			lst = lst->next;
		returnable = &(*new_lst);
		while (lst)
		{
			new_lst->next = f(lst);
			lst = lst->next;
			new_lst = new_lst->next;
		}
		new_lst->next = NULL;
		return (returnable);
	}
	return (NULL);
}
