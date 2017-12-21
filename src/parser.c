# include "cookielem-in.h"
# include "get_next_line.h"


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

static int check_tubes(t_map *map, char *line){

	// comment etre sur que je passe l adresse de data a chaque fois et non data en copie?
	// t_room res[2];
	int 	i = 0; // pour tester le retour du split
	t_room 	*ptr;
	char 	**tube_data;
	char 	status = 0;

	ptr = map->rooms;
	tube_data = ft_strsplit(line, '-');
	while (tube_data[i] != NULL)
		i++;
	if (i!= 2)
	{
		ft_putendl("error format input\n");
		return(-1);
	}

	ft_memset(map->tmp, 0, sizeof(t_room*) * 2);

	while (ptr && status != 2)
	{
		if (!(ft_strcmp(tube_data[0], ptr->name)))
			{
				status += 1;
				map->tmp[0] = ptr;
			}
		if (!(ft_strcmp(tube_data[1], ptr->name)))  // if si on veut qu il passe dans les deux
			{
				status += 1;
				map->tmp[1] = ptr;
			}
		ptr = ptr->next;
	}
	if (status == 2)
	{
		// printf("status vaut 2\n");
		connect_rooms(map);
		// printf("print & de map->rooms->tubes stored : %p", map->rooms->tubes->room);

	}
	return (status); //si retourne 1 ou 0 signifie erreur ou detail 1 une seule
	//salle existe, 0 aucune des salles existe
}


static void	push_room(t_map *map, t_room *room)
{
	t_room *tmp;

	tmp = map->rooms;
	while (tmp->next)
			tmp = tmp->next;
	tmp->next = room;
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

static int linetodata(t_map *map, char *line, int p_status)
{
	char 	**data;
	t_room 	*room;
	//int ret;



	static char	iffirstroom = 1;
	int i = 0;
	char 		status = ROOM;

	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		{
			ft_putendl(ERR_ALLOC);
			exit(-1);
		}
		if (ft_strchr(line, '-'))
			status = TUBE;

	if ((data = ft_strsplit(line, ' ')) == NULL )
		{
			ft_putendl("Error");
			status = ERROR;
			exit(-1);
		}

	while (data[i] != NULL)
		i++;

	if ((status == ROOM) && i == 3)
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
		if (iffirstroom == 1)
		{
			map->rooms = room;
			iffirstroom = 0;
		}
		else
			push_room(map, room);
	}


	//printf("%s\n", line);
	if (status == TUBE && i == 1)
		{
			//printf("tube\n");
			// if(map->start && map->end)
			// 	printf("start : %s, end : %s\n", map->start->name, map->end->name);
				// printf("parse_tube();");
				// if ((ret = parse_tubes(map, data[0], data[1])) != 2)
				// 	{
				// 		printf("error while parsing tubes : %d", ret);
				// 		return (-1);
				// 	}
				if (ft_strchr(line, '-')){
					//printf("OK line de tube !\n");
					if ((check_tubes(map, line)) != 2)
						return (-1);
				}

		}

	/*
	** Test type data (room ou tube) =====strchr()!
	*/

	return (1);
}

static int ifisdigit(char *line){
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

	status = NO_ANT;
	line = NULL;

	while(ret != 0)
	{

		if ((ret = get_next_line(0, &line)) < 0)
		{
			ft_putendl(ERR_READ);
			exit(-1);
		}
		if (ret == 0)
		break;
	 	if (ret && *line && ifisdigit(line) && !status)
		{
			map->ant = ft_atoi(line);
			status = ANT;
		}
		else if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				if (!(ft_strcmp(line + 2, "start")))
			 		status = START;
				else if (!(ft_strcmp(line + 2, "end")))
			 		status = END;
			}
			else
				continue;
		}
		else
		{
				if ((linetodata(map, line, status)) == -1)
					{
						printf("Error line to data, stop parsing\n");
						//break;
					}
			status = ANT;
		}
		free(line);
	}
		// printf("Liste des rooms\n");
		 room_print(map->rooms);


	return (1);
}
