/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/03 19:37:55 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../include/lem-in.h"

void	panic(char *str)
{
	ft_putstr(str);
	exit(EXIT_FAILURE);
}

int		atoi_next_line(int fd, int *val)
{
	int		ret;
	char	*str;

	ret = get_next_line(fd, &str);
	*val = ft_atoi(str);
	ft_memdel((void **)&str);
	return (ret);
}

t_env	parser(void)
{
	t_env	env;
	char	*str;

	if (atoi_next_line(0, &(env.atstart)) != 1)
		panic("Parse error\n");
	return (env);
}

int		main(void)
{
	return (0);
}
