
#include "lem-in.h"
#include "parser_lem-in.h"

static void clean_conflict(t_conflit *conflit)
{
	while(conflit->next)
		conflit = conflit->next;
	while(conflit->prev)
	{
		conflit = conflit->prev;
		ft_memdel((void**)&conflit->next);
	}
	ft_memdel((void**)&conflit);
}

int save_info(int set, int new_depth, t_room *o_room, t_room *n_room, t_env *env)
{
	static t_conflit *conflict = NULL;

	if (set == 0)
	{
			if (!conflict)
				conflict = ft_memalloc(sizeof(t_conflit));
			conflict->len = new_depth;
			conflict->old_room = o_room;
			conflict->miss_direction = n_room;
			conflict->next = ft_memalloc(sizeof(t_conflit));
			conflict->next->prev = conflict;
			conflict = conflict->next;
	}
	else
	{
		while((set++ - env->conflict) < 1)
				conflict = conflict->prev;
		if (env->antleft >= conflict->len && env->antleft >= new_depth)
		{
			conflict->old_room->prev = conflict->miss_direction;
			clean_conflict(conflict);
			conflict = NULL;
			return(TRUE);
		}
		clean_conflict(conflict);
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
			room->lock = -1;
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
		if (env->rooms[i]->lock != -1)
			env->rooms[i]->weight = 0;
		if (env->rooms[i]->lock != -1)
			env->rooms[i]->lock = 0;
		else
			env->rooms[i]->lock = 1;
		env->rooms[i]->dead = 0;
	}
}
