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

enum { NO_ANT, ANT, START, END };
enum { ROOM, TUBE, ERROR, LICORNE };

typedef struct s_tube
{
	struct s_room *room;
	struct s_tube *next;
}		t_tube;

typedef struct s_room
{
	char 	*name;
	int		x;
	int		y;
	t_tube	*tubes;
	t_tube *a_tube;
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
	t_tube		*tubes;
	t_room		*tmp[2]; //p1 p2
}		t_map;

int parser(t_map *map);

# endif