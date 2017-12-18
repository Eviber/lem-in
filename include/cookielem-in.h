#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdio.h>
# include <sys/types.h>

#define ERR_READ "error while reading stdin\n"
#define ERR_DIGIT "error while checking digit format\n"
#define ERR_ALLOC "error while allocating memory\n"

#define TRUE 1;
#define FALSE 0;

typedef struct s_room
{
	char 	*name;
	int		x;
	int		y;
	struct s_room	**tubes;
	struct s_room 	*next;
	int 	weight;
//	t_bool 	visited;
}		t_room;

typedef struct	s_map
{
	int			ant;
	int			antleft;
	t_room		*rooms;
	t_room		*start;
	t_room		*end;
	t_room		**roads;
}		t_map;

void parser(t_map *map);

# endif
