/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:29:16 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/11 17:19:30 by ygaude           ###   ########.fr       */
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
/*
int		parse_room(t_env *env, char *str)
{
	return (0);
}

int		parse_tube(t_env *env, char *str)
{
	return (0);
}
*/
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

/*
** Bourrin du cul
*/

t_env	parser(void)
{
	t_env	env;
	t_room	*rooms;
	t_room	**tmp;

	rooms = (t_room *)malloc(sizeof(t_room) * 8);
	tmp = (t_room **)malloc(sizeof(t_room) * 2);
	tmp[0] = &rooms[4];
	tmp[1] = &rooms[6];
	rooms[0] = (t_room){ tmp, {23, 3}, "a", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 2);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[3];
	rooms[1] = (t_room){ tmp, {16, 7}, "b", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[1];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[7];
	rooms[2] = (t_room){ tmp, {16, 3}, "c", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[1];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[8];
	rooms[3] = (t_room){ tmp, {16, 5}, "d", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 4);
	tmp[0] = &rooms[0];
	tmp[1] = &rooms[1];
	tmp[2] = &rooms[2];
	tmp[3] = &rooms[7];
	rooms[4] = (t_room){ tmp, {9, 3}, "e", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[3];
	tmp[2] = &rooms[6];
	rooms[5] = (t_room){ tmp, {1, 5}, "f", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[0];
	tmp[1] = &rooms[5];
	tmp[2] = &rooms[7];
	rooms[6] = (t_room){ tmp, {4, 8}, "g", 2, 0 };
	tmp = (t_room **)malloc(sizeof(t_room) * 3);
	tmp[0] = &rooms[2];
	tmp[1] = &rooms[4];
	tmp[2] = &rooms[6];
	rooms[7] = (t_room){ tmp, {9, 5}, "h", 2, 0 };
	env.start = &rooms[1];
	env.end = &rooms[0];
	return (env);
}

int		main(void)
{
	t_env	env;

	env = parser();
	return (0);
}
