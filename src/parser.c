# include "cookielem-in.h"
# include "get_next_line.h"

void ft_error(unsigned long motif)
{
	if (motif == 1)
		ft_putendl(ERR_ALLOC);
	else if (motif == 2)
		ft_putendl("Error");
	else if (motif == 3)
		ft_putendl("error format input\n");
	exit(-1);
}

static void connect_rooms(t_map *map){
	t_room *ptr1 = map->tmp[0];
	t_room *ptr2 = map->tmp[1];

	ptr1->tubes = ptr1->a_tube;
	ptr2->tubes = ptr2->a_tube;
	while (ptr1->tubes->room)
		ptr1->tubes = ptr1->tubes->next;
	while (ptr2->tubes->room)
		ptr2->tubes = ptr2->tubes->next;
	ptr1->tubes->room = ptr2;
	ptr2->tubes->room = ptr1;
	ptr1->tubes->next = (t_tube*)ft_memalloc(sizeof(t_tube));
	ptr2->tubes->next = (t_tube*)ft_memalloc(sizeof(t_tube));
}

static int check_tubes(t_map *map, char *line)
{
	int 	i;
	t_room 	*ptr;
	char 	**tube_data;
	char 	status;

	i = 0;
	status = 0;
	ptr = map->rooms;
	tube_data = ft_strsplit(line, '-');
	while (tube_data[i] != NULL)
		i++;
	if (i!= 2)
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


static void	push_room(t_map *map, t_room *room)
{
	t_room *tmp;

	if (!map->rooms)
		map->rooms = room;
	else
	{
		tmp = map->rooms;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = room;
	}
}

static void	room_print(t_room *room){

	t_room *ptr = room;

	while (ptr)
	{
		ft_putendl(ptr->name);
		ptr->tubes = ptr->a_tube;
		while (ptr->tubes->room)
		{
			printf("%s - %s\n", ptr->name, ptr->tubes->room->name);
			ptr->tubes = ptr->tubes->next;
		}
		ptr = ptr->next;
	}
}

static void init_room(t_map *map, t_room *room, char **data, int p_status)
{
	room->name = ft_strdup(data[0]);
	room->x = ft_atoi(data[1]);
	room->y = ft_atoi(data[2]);
	room->next = NULL;
	room->tubes = ft_memalloc(sizeof(t_tube));
	room->a_tube = 	room->tubes;
	if (p_status == START)
		map->start = room;
	else if (p_status == END)
		map->end = room;
	push_room(map, room);
}



static int linetodata(t_map *map, char *line, int p_status)
{
	char 	**data;
	t_room 	*room;
	int i;
	char 	status;

	i = 0;
	status = ROOM;
	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		ft_error(1);
	if (ft_strchr(line, '-'))
		status = TUBE;
	if ((data = ft_strsplit(line, ' ')) == NULL )
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

static int ifisdigit(char *line)\
{
	int i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (!ft_isdigit(line[i]))
			return(0);
		else
			i++;
	}
	return (1);
}


int parser(t_map *map)
{
	char 	*line;
	int		status; /*0:no ant, 1:ant done, 2:start or 3:end */
	int		test;

	status = NO_ANT;
	line = NULL;
	while((get_next_line(0, &line)) > 0)
	{
		if (*line && ifisdigit(line) && !status && (status = ANT))
			map->ant = ft_atoi(line);
		if (line[0] == '#' && line[1] == '#')
		{
			status = ((test = !(ft_strcmp(line + 2, "start")) +
						(!ft_strcmp(line + 2, "end") * 2)) ? ANT + test : status);
		}
		else
			if ((status = ANT) && (linetodata(map, line, status)) == -1)
				break;
		ft_putendl(line);
		free(line);
	}
	room_print(map->rooms);
	return (1);
}
