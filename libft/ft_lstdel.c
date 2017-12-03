/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:57:00 by ygaude            #+#    #+#             */
/*   Updated: 2016/11/30 17:26:52 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*pnode;
	t_list	*next;

	pnode = *alst;
	while (pnode)
	{
		next = pnode->next;
		ft_lstdelone(&pnode, del);
		pnode = next;
	}
	*alst = NULL;
}
