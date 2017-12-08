/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/08 21:10:50 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../include/lem-in.h"

void	panic(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

int		atoi_next_line(int fd, int *val)
{
	int		ret;
	char	*str;

	if ((ret = get_next_line(fd, &str)) != -1)
	{
		*val = ft_atoi(str);
		ft_strdel(&str);
	}
	return (ret);
}

int		parse_room(t_env *env, char *str)
{
}

int		parse_tube(t_env *env, char *str)
{
}

int		whatis(char *str)
{
	if(str[0] == '#')
	{
		if (ft_strequ(str, "##start"))
			return (START);
		else if (ft_strequ(str, "##end"))
			return (END);
		else
			return (COMM);
	}
	if (ft_strchr(str, '-') && !ft_strchr(str, ' '))
		return (TUBE);
	return (ROOM);
}

t_env	parser(void)
{
	t_env	env;
	char	*str;
	char	*buf;
	int		ret;
	int		type;
	int		err;
	int		tube;
	int		next;

	tube = 0;
	if ((ret = atoi_next_line(0, &(env.atstart))) != 1)
		panic((!ret) ? "Parse error\n" : "Read error\n");
	while (ret)
	{
		if ((ret = get_next_line(0, &buf)) == -1)
			panic("Read error\n");
		type = whatis(buf);
		tube = (type == TUBE) ? 1 : tube;
		if (type < COMM)
		{
			if (tube)
			{
				err = parse_tube(&env, buf);
			}
			else
			{
				err = parse_room(&env, buf);
			}
		}
		next = (type == START || type == END) ? type : 0;
		ft_strdel(&buf);
	}
	return (env);
}

int		main(void)
{
	return (0);
}
