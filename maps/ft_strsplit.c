/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 16:59:10 by vsporer           #+#    #+#             */
/*   Updated: 2017/09/22 20:01:30 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbwords(char const *s, char c)
{
	size_t	nbwords;
	size_t	i;
	int		f;

	nbwords = 0;
	i = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] != c && f == 0)
		{
			f = 1;
			nbwords++;
		}
		if (s[i] == c && f == 1)
			f = 0;
		i++;
	}
	return (nbwords);
}

static char		*ft_getword(char const *s, char c, size_t i)
{
	size_t	j;
	char	*word;

	j = 0;
	while (s[i] == c)
		i++;
	while (s[i + j] && s[i + j] != c)
		j++;
	if ((word = (char*)malloc(sizeof(char) * (j + 1))))
	{
		j = 0;
		while (s[i + j] && s[i + j] != c)
		{
			word[j] = s[i + j];
			j++;
		}
		word[j] = 0;
		return (word);
	}
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**splitw;
	size_t	i;
	size_t	size;
	size_t	index;

	i = 0;
	index = 0;
	size = (s) ? ft_nbwords(s, c) : 0;
	if ((splitw = (char**)malloc(sizeof(char*) * size + 1)) && s)
	{
		while (index < size)
		{
			while (s[i] == c)
				i++;
			if (!(splitw[index] = ft_getword(s, c, i)))
				return (NULL);
			index++;
			while (s[i] && s[i] != c)
				i++;
		}
		splitw[index] = NULL;
		return (splitw);
	}
	return (NULL);
}
