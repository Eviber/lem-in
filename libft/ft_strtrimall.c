/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 07:45:58 by sbrochar          #+#    #+#             */
/*   Updated: 2018/02/07 16:21:52 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define CHECK_SPACE(x) (x == ' ' || x == '\n' || x == '\t')
#define CHECK_BLANKS(x) (x == '\v' || x == '\f' || x == '\r')

static size_t		get_len(char const *s)
{
	size_t			ret;
	size_t			words;

	ret = 0;
	words = 0;
	while (s && *s)
	{
		while (*s && (CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
			s++;
		if (*s && !(CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
			words++;
		while (*s && !(CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
		{
			s++;
			ret++;
		}
	}
	return (ret + words - 1);
}

static void			copy_str(char const *s, char **new, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		while (*s && (CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
			s++;
		while (*s && !(CHECK_SPACE(*s) || CHECK_BLANKS(*s)))
		{
			(*new)[i] = *s;
			i++;
			s++;
		}
		if (i < len)
		{
			(*new)[i] = ' ';
			i++;
		}
	}
}

char				*ft_strtrimall(char const *s)
{
	char			*ret;
	size_t			len;

	len = get_len(s);
	ret = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (ret)
	{
		copy_str(s, &ret, len);
		return (ret);
	}
	return (NULL);
}
