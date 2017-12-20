# include "cookielem-in.h"
# include "get_next_line.h"


static void connect_rooms(t_map *map){
	t_room *ptr1 = map->tmp[0];
	t_room *ptr2 = map->tmp[1];

	ptr1->tubes->room = ptr2;
	ptr2->tubes->room = ptr1;
}

static int parse_tubes(t_map *map, char *data1, char *data2){

	// comment etre sur que je passe l adresse de data a chaque fois et non data en copie?
	t_room res[2];
	t_room *ptr = NULL;
	/*allocation? a la fin de la function si ok on a trouve les deux names/*/
	char status = 0;

	ptr = map->rooms;
	while (ptr && status != 2)
	{
		if (!(ft_strcmp(data1, ptr->name)))
			{
				status += 1;
				res[0] = ptr;
			}
		if (!(ft_strcmp(data2, ptr->name)))  // if si on veut qu il passe dans les deux
			{
				status += 1;
				res[1] = ptr;
			}
		if (status == 2){
			//alors il sera passe dans les deux boucles et on aura les deux names ok
			store_tube();
		}
		ptr = ptr->next;
	}
	if (status == 2)
		{
			map.tmp[0] = res[0];
			map.tmp[1] = res[1];
			connect_rooms(&map);//est ce que ca va marcher normalement je passe des &
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
		ptr = ptr->next;
	}
}

static int linetodata(t_map *map, char *line, int status)
{
	char 	**data;
	t_room 	*room;
	int ret;

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
				printf("parse_tube();");
				if ((ret = parse_tubes(&map, data[0], data[1]) != 2)
					{
						printf("error while parsing tubes : %d", ret);
						return (-1);
					}
			if (i!= 2)
				{
					ft_putendl("error format input\n");
					return(-1); /*si pas EXIT on met quoi?*/
				}
		}
	room->name = ft_strdup(data[0]);
	room->x = ft_atoi(data[1]);
	room->y = ft_atoi(data[2]);
	room->next = NULL;
	/*
	** Test type data (room ou tube) =====strchr()!
	*/
	if (status == START)
		map->start = room;
	else if (status == END)
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

	 	if (*line && ifisdigit(line) && !status)
		{
			//printf("STATUS 0\n");
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
				if ((linetodata(map, line, status)) != 0)
					{
						printf("Error line to data, stop parsing\n");
						break;
					}
			status = ANT;
		}
		free(line);
	}

		room_print(map->rooms);


	return (1);
}
