
#include "lem_in.h"
#include "parser_lem_in.h"

static void	clean_conflict(t_conflit **conflit)
{
	while ((*conflit)->next)
		*conflit = (*conflit)->next;
	while ((*conflit)->prev)
	{
		*conflit = (*conflit)->prev;
		ft_memdel((void**)&((*conflit)->next));
	}
	ft_memdel((void**)conflit);
}

static int	search_conf(t_conflit **conf, int set, int new_dp, t_env *env)
{
	while ((set++ - env->conflict) < 1)
		*conf = (*conf)->prev;
	if (env->antleft >= (*conf)->len && env->antleft >= new_dp)
	{
		(*conf)->old_room->prev = (*conf)->miss_direction;
		clean_conflict(conf);
		return (TRUE);
	}
	clean_conflict(conf);
	return (FALSE);
}

int			save_info(int set, int new_dp, t_room *room, t_env *env)
{
	static t_conflit *conflict = NULL;

	if (set == -1)
	{
		if (!conflict)
			conflict = ft_memalloc(sizeof(t_conflit));
		conflict->len = new_dp;
		conflict->old_room = room;
		conflict->next = ft_memalloc(sizeof(t_conflit));
		conflict->next->prev = conflict;
		conflict = conflict->next;
	}
	else if (set == 0)
		conflict->prev->miss_direction = room;
	else if (set > 0)
		return (search_conf(&conflict, set, new_dp, env));
	return (FALSE);
}

void		lock_path(t_env *env)
{
	t_path	*tmp;
	t_room	*room;
	int		len;

	env->antleft = env->nb_ants;
	tmp = env->paths;
	while (tmp && tmp->room)
	{
		room = tmp->room;
		len = 1;
		room->next = env->end;
		while (room && room->prev)
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

void		reset_room(t_env *env)
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
