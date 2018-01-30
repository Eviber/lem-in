
#include "lem-in.h"
#include "parser_lem-in.h"
#include "solver.h"

void conflit(t_room *rooms, t_env *env, long depth, t_room *room_confict)
{
	long	dp;
	long tmp_dp;
	t_room *tmp;

	tmp = rooms;
	while(tmp->next != env->end)
	 	tmp = tmp->next;
	dp = tmp->weight;
	env->antleft += dp;
	tmp_dp = depth + 1;
	tmp = rooms->prev;
	++env->conflict;
	while(tmp->prev)
	{
		tmp->lock = env->conflict ;
		tmp->weight = --tmp_dp;
		tmp = tmp->prev;
	}
	env->depth = tmp_dp;
	depth = depth + 1 - rooms->weight + dp;
	rooms->dead = 1;
	save_info(0, depth, rooms, room_confict, env);
}

static int		fill_weight(t_env *env, t_room *room)
{
	int		i;

	i = 0;
	while (room->pipes && room->pipes[i])
	{
		if (room->pipes[i] == env->end)
		{
			if (room->lock == 0 || save_info(room->lock, room->weight +1, NULL, NULL, env))
				return (TRUE);
			}
		if (!room->pipes[i]->weight && room->pipes[i] != env->start && (room->pipes[i]->lock != 1 || room == env->start))
		{
			room->pipes[i]->weight = room->weight + 1;
			room->pipes[i]->prev = room;
			room->pipes[i]->lock = room->lock;
		}
	   if (room != env->start && room->pipes[i]->lock == 1 && !room->pipes[i]->dead && !room->lock)
		 {
			 conflit(room->pipes[i], env, room->weight, room);
			 return(FALSE);
		 }
		i++;
	}
	return (FALSE);
}

t_room	*try_path(t_env *env, int depth)
{
	t_room	*cur;
	int		i;

	i = 0;
	while (env->rooms[i])
	{
		cur = env->rooms[i++];
		if (cur->weight == depth - 1 && cur->lock != 1 && (cur->weight || cur == env->start))
			if (fill_weight(env, cur))
				return (cur);
	}
	return (NULL);
}

int				find_shortest(t_env *env, int f_iter)
{
	t_room *tmp;
	static t_room *f_room = NULL;

	env->depth = 1;
	while (env->depth <= env->nb_rooms - 1 && (f_iter == 0 || env->depth < env->nb_ants + 1))
	{
		if ((tmp = try_path(env, env->depth++)))
			if (tmp != f_room)
			{
				if (!f_room)
					f_room = tmp;
				if (!env->paths->room )
					env->paths->room  = tmp;
				return (TRUE);
			}
	}
	return (FALSE);
}
void get_path(t_env *env)
{
  t_room *tmp;
  int i;

  i = 0;
	env->paths = (t_path *)ft_memalloc(sizeof(t_path));
  while (find_shortest(env, i))
  {
		env->conflict = 1;
		i++;
    tmp = env->paths->room;
		tmp->next = env->end;
		lock_path(env);
		reset_room(env);
    env->paths->next = (t_path *)ft_memalloc(sizeof(t_path ));
    env->paths->next->prev = env->paths;
    env->paths = env->paths->next;
  }
	if (!env->paths->room &&  env->paths->prev)
		env->paths = env->paths->prev;
	lock_path(env);
}
