/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: demodev <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 15:20:15 by demodev           #+#    #+#             */
/*   Updated: 2017/09/04 22:21:31 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ftplst	*ft_ftplstnew(char *flag)
{
	t_ftplst	*new;

	if ((new = (t_ftplst*)malloc(sizeof(t_ftplst))))
	{
		if (flag)
			new->flag = flag;
		else
			new->flag = NULL;
		new->flag_ok = 0;
		new->sharp = 0;
		new->zero = 0;
		new->minus = 0;
		new->space = 0;
		new->sign = 0;
		new->field = 0;
		new->prec = 0;
		new->nullchar = 0;
		new->arg = NULL;
		new->clean_flag = NULL;
		new->size = 0;
		new->index.i = 0;
		new->index.j = 0;
		new->next = NULL;
	}
	return (new);
}

void		ft_ftplstaddback(t_ftplst **alst, t_ftplst *new)
{
	t_ftplst	*tmp;

	if (!*alst)
		*alst = new;
	else
	{
		tmp = *alst;
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
		*alst = tmp;
	}
}

void		ft_ftplstdel(t_ftplst **todel)
{
	t_ftplst	*tmp;

	if (*todel)
	{
		tmp = (*todel)->next;
		if ((*todel)->arg)
		{
			ft_bzero((*todel)->arg, ft_strlen((*todel)->arg));
			ft_strdel(&(*todel)->arg);
		}
		if ((*todel)->flag)
		{
			ft_bzero((*todel)->flag, ft_strlen((*todel)->flag));
			ft_strdel(&(*todel)->flag);
		}
		if ((*todel)->clean_flag)
		{
			ft_bzero((*todel)->clean_flag, ft_strlen((*todel)->clean_flag));
			ft_strdel(&(*todel)->clean_flag);
		}
		ft_memdel((void**)todel);
		*todel = tmp;
	}
}
