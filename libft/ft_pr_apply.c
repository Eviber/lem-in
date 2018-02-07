/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 19:46:25 by ygaude            #+#    #+#             */
/*   Updated: 2017/10/25 20:59:52 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

void	ft_norme_prefix(t_str *res, int opt[8], char spec, int sign)
{
	char	*tmp;

	tmp = (spec == 'b') ? "0b" : "0x";
	if ((spec == 'o' || spec == 'O') && (sign || !opt[PREC]))
	{
		if (res->len < (size_t)opt[PREC] && opt[PREC] != -1)
			opt[PREC] = opt[PREC];
		else
			opt[PREC] = res->len + 1;
	}
	else if (sign || spec == 'p')
	{
		res->len += 2;
		opt[PREFIX] += 2;
		opt[PREC] += 2;
		res->str = ft_strappend(&tmp, &(res->str), 'S');
	}
}

void	ft_norme_prec(t_str *res, int opt[8], int sign)
{
	char	*tmp;

	tmp = ft_strnew(opt[PREC] - res->len + (sign < 0));
	tmp = ft_memset(tmp, '0', opt[PREC] - res->len + (sign < 0));
	res->str = ft_strinsert(&tmp, &(res->str), opt[PREFIX], 'B');
	res->len = (size_t)opt[PREC] + (sign < 0);
}

t_str	ft_applyint(t_str res, int opt[8], char spec)
{
	int		sign;
	char	*tmp;

	sign = (res.str[0] == '-') ? -1 : (res.str[0] != '0');
	opt[PREFIX] += (sign < 0);
	if (!sign && !opt[PREC] && !(res.len = 0))
	{
		ft_strdel(&(res.str));
		res.str = ft_strnew(0);
	}
	if (spec == 'p' || (opt[HASH] && ft_strchr("boOxX", spec)))
		ft_norme_prefix(&res, opt, spec, sign);
	if (res.len - (sign < 0) < (size_t)opt[PREC] && opt[PREC] != -1)
		ft_norme_prec(&res, opt, sign);
	if ((opt[SPACE] || opt[PLUS]) && sign >= 0 && ft_strchr("dDi", spec))
	{
		tmp = (opt[PLUS]) ? "+" : " ";
		res.str = ft_strappend(&tmp, &(res.str), 'S');
		res.len++;
		opt[PREFIX]++;
	}
	return (res);
}

t_str	ft_norme_width(t_str res, int opt[8], char spec)
{
	t_str	space;
	char	c;

	if (opt[WIDTH] < 0)
	{
		opt[WIDTH] = -opt[WIDTH];
		opt[MINUS] = 1;
	}
	space.len = ((size_t)opt[WIDTH] > res.len) ? opt[WIDTH] - res.len : 0;
	space.str = ft_strnew(space.len);
	c = (!opt[MINUS] && opt[ZERO] &&
			(opt[PREC] == -1 || !ft_strchr("dDioOuU", spec))) ? '0' : ' ';
	space.str = ft_memset(space.str, c, space.len);
	if (opt[MINUS])
		res = ft_chunkappend(res, space, 'F');
	else if (space.str[0] == '0' && space.len)
	{
		res.str = ft_strinsert(&(space.str), &(res.str), opt[PREFIX], 'S');
		res.len += space.len;
	}
	else if (space.len)
		res = ft_chunkappend(space, res, 'S');
	ft_strdel(&(space.str));
	return (res);
}

t_str	ft_apply(t_str res, int opt[8], char spec)
{
	int		prec;

	prec = opt[PREC];
	if (ft_strchr("sScC", spec))
	{
		if (spec != 'c' && spec != 'C' && res.len > (size_t)prec && prec != -1)
			res.len = opt[PREC];
	}
	else if (ft_strchr(SPECIFIER, spec))
		res = ft_applyint(res, opt, spec);
	res = ft_norme_width(res, opt, spec);
	if (spec == 'X')
		ft_strtoupper(res.str);
	return (res);
}
