# include "cookielem-in.h"
# include "get_next_line.h"

void	push_room(t_map *map, t_room *room)
{
	t_room *tmp;

	tmp = map->rooms;
	while (tmp->next)
			tmp = tmp->next;
	tmp->next = room;
}

void	room_print(t_room *room){

	t_room *ptr = room;

	while (ptr)
	{
		ft_putendl(ptr->name);
		ptr = ptr->next;
	}
}

int linetodata(t_map *map, char *line, int status)
{
	char 	**data;
	t_room 	*room;
	static char	iffirstroom = 1;
	int i = 0;

	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		{
			ft_putendl(ERR_ALLOC);
			exit(-1);
		}
	if ((data = ft_strsplit(line, ' ')) == NULL )
		{
			ft_putendl("Error");
			exit(-1);
		}

	while (data[i] != NULL)
		i++;
	if (i != 3)
		{
			room_print(map->rooms);
			if(map->start && map->end)
				{
					printf("start : %s, end : %s\n", map->start->name, map->end->name);
				}
			ft_putendl("error format input\n");
			exit(-1); /*si pas EXIT on met quoi?*/
		}
	room->name = ft_strdup(data[0]);
	room->x = ft_atoi(data[1]);
	room->y = ft_atoi(data[2]);
	room->next = NULL;
	/*
	** Test type data (room ou tube) =====strchr()!
	*/
	if (status == 2)
		map->start = room;
	else if (status == 3)
		map->end = room;
	if (iffirstroom == 1)
	{
		map->rooms = room;
		iffirstroom = 0;
	}
	else
		push_room(map, room);
	//room_print(map->rooms);
	return (1);
}

int ifisdigit(char *line){
	int i = 0;

	while (line && line[i] != '\0'){
		if (!ft_isdigit(line[i]))
			return(0);
		else
			i++;
	}
	return (1);
}


int parser(t_map *map){

	int 	ret = 1;
	char 	*line;
	int		status; /*0:no ant, 1:ant done, 2:start or 3:end */

	status = 0;
	line = NULL;

	while(ret != 0)
	{

		if ((ret = get_next_line(0, &line)) < 0)
		{
			ft_putendl(ERR_READ);
			exit(-1);
		}

	 	if (*line && ifisdigit(line) && !status)
		{
			//printf("STATUS 0\n");
			map->ant = ft_atoi(line);
			status = 1;
		}
		else if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				if (!(ft_strcmp(line + 2, "start")))
			 		status = 2;
				else if (!(ft_strcmp(line + 2, "end")))
			 		status = 3;
			}
			else
				continue;
		}
		else
		{
			linetodata(map, line, status);
			status = 0;
		}
		free(line);
	}

		room_print(map->rooms);


	return (1);
}
