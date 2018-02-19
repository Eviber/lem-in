#include "lem-in.h"
#include "parser_lem-in.h"

int save_info(int set, int new_depth, t_room *o_room, t_room *n_room, t_env *env)
{
	static long depth = 0;
	static t_room *old_room = NULL;
	static t_room *miss_direction = NULL;

	if (set)
	{
			depth = new_depth;
			old_room = o_room;
			miss_direction = n_room;
	}
	else
	{
		if (env->antleft >= depth && env->antleft >= new_depth)
		{
			old_room->prev = miss_direction;
			return(TRUE);
		}
	}
	return(FALSE);
}

void lock_path(t_env *env)
{
	t_path *tmp;
	t_room *room;
	int		len;

	env->antleft = env->nb_ants;
	tmp = env->paths;
	while(tmp && tmp->room)
	{
		room = tmp->room;
		len = 1;
		room->next = env->end;
		while(room && room->prev)
		{
			room->prev->next = room;
			room->lock = 3;
			room = room->prev;
			len++;
		}
		tmp->length = len;
		env->antleft -= len;
		tmp = tmp->prev;
	}
}

void reset_room(t_env *env)
{
	int i;

	i = -1;
	while (env->rooms[++i])
	{
		if (env->rooms[i]->lock != 3)
			env->rooms[i]->weight = 0;
		if (env->rooms[i]->lock != 3)
			env->rooms[i]->lock = 0;
		else
			env->rooms[i]->lock = 1;
		env->rooms[i]->dead = 0;
	}
}
