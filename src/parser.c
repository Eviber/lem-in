# include "cookielem-in.h"
# include "get_next_line.h"

void linetodata(t_map *map, char *line, int status)
{
	char 	**data;
	t_room 	*room;
	char	iffirstroom = 1;

	if ((room = (t_room*)ft_memalloc(sizeof(t_room))) == NULL)
		{
			ft_putendl(ERR_ALLOC);
			exit(-1);
		}
	data = ft_strsplit(line, ' ');
	room->name = ft_strdup(data[0]);
	room->x = ft_atoi(data[1]);
	room->y = ft_atoi(data[2]);
	/*
	** Test type data (room ou tube) =====strchr()!
	*/
	if (status == 2)
		map->start = room;
	else if (status == 3)
		map->end = room;
	else if (!iffirstroom)
		map->rooms->next = room;
	else
	{
		map->rooms = room;
		iffirstroom = 0;
	}
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


void parser(t_map *map){

	int 	ret = 1;
	char 	*line;
	int		status; /*0:no ant, 1:ant done, 2:start or 3:end */

	status = 0;
	line = NULL;

	while(ret != 0)
	{
		if (status == 2 || status == 3){
			linetodata(map, line, status);
			status = 1;
		}
		if ((ret = get_next_line(0, &line)) == -1)
		{
			ft_putendl(ERR_READ);
			exit(-1);
		}
		else if (*line && ifisdigit(line) && !status)
		{
			map->ant = ft_atoi(line);
			status = 1;
		}
		else if (line[0] == '#')
		{
			if (line[1] == '#')
			{
				if (!(ft_strcmp(line + 2, "start")))
			 		status = 2; // on peut mettre un ternaire ici ? ==> sans faille de parser?
				else if (!(ft_strcmp(line + 2, "end")))
			 		status = 3;
			}
			else
				continue; /*would be a # comment line though*/
		}
		else
			linetodata(map, line, status);
	}
	free(line);
}
