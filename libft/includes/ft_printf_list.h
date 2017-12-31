/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 16:47:28 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/04 22:06:25 by demodev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_LIST_H
# define FT_PRINTF_LIST_H

# include "ft_printf.h"

typedef struct	s_index
{
	int		i;
	int		j;
}				t_index;

typedef struct	s_ftplst
{
	int				flag_ok;
	int				sharp;
	int				zero;
	int				minus;
	int				space;
	int				sign;
	int				field;
	int				prec;
	int				nullchar;
	char			*arg;
	char			*flag;
	char			*clean_flag;
	size_t			size;
	t_index			index;
	struct s_ftplst	*next;
}				t_ftplst;

t_ftplst		*ft_ftplstnew(char *flag);
void			ft_ftplstaddback(t_ftplst **alst, t_ftplst *new);
void			ft_ftplstdel(t_ftplst **todel);

#endif
