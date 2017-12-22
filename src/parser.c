/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourmea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:51:52 by pbourmea          #+#    #+#             */
/*   Updated: 2017/12/22 19:53:11 by pbourmea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cookielem_in.h"
#include "get_next_line.h"

static int	check_tubes(t_map *map, char *line)
{
	int		i;
	t_room	*ptr;
	char	**tube_data;
	char	status;

	i = 0;
	status = 0;
	ptr = map->rooms;
	tube_data = ft_strsplit(line, '-');
	while (tube_data[i] != NULL)
		i++;
	if (i != 2)
		ft_error(3);
	ft_memset(map->tmp, 0, sizeof(t_room*) * 2);
	while (ptr && status != 2)
	{
		if (!(ft_strcmp(tube_data[0], ptr->name)) && ++status)
			map->tmp[0] = ptr;
		if (!(ft_strcmp(tube_data[1], ptr->name)) && ++status)
			map->tmp[1] = ptr;
		ptr = ptr->next;
	}
	if (status == 2)
		connect_rooms(map);
	return (status);
}

static int	linetodata(t_map *map, char *line, int p_status)
{
	char	**data;
	t_room	*room;
	int		i;
	char	status;

	i = 0;
	status = ROOM;
	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		ft_error(1);
	if (ft_strchr(line, '-'))
		status = TUBE;
	if ((data = ft_strsplit(line, ' ')) == NULL)
		ft_error(2);
	while (data[i] != NULL)
		i++;
	if ((status == ROOM) && i == 3)
		init_room(map, room, data, p_status);
	if (status == TUBE && i == 1 && ft_strchr(line, '-'))
		if ((check_tubes(map, line)) != 2)
			return (-1);
	return (1);
}

int			parser(t_map *map)
{
	char	*line;
	int		status;
	int		test;

	status = NO_ANT;
	line = NULL;
	while ((get_next_line(0, &line)) > 0)
	{
		if (*line && ft_strisdigit(line) && !status && (status = ANT))
			map->ant = ft_atoi(line);
		if (line[0] == '#' && line[1] == '#')
		{
			test = !(ft_strcmp(line + 2, "start")) +
			(!ft_strcmp(line + 2, "end") * 2);
			status = ((test) ? ANT + test : status);
		}
		else if ((linetodata(map, line, status)) == -1 || !(status = ANT))
			break ;
		ft_putendl(line);
		free(line);
	}
	//room_print(map->rooms);
	return (1);
}
