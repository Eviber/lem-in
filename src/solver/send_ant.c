
#include "lem_in.h"
#include "parser_lem_in.h"
#include "solver.h"

char *create_string(unsigned long nb_ant, char *room)
{
	char	*res;
	char	*char_ant;
	int		i;
	int		j;

	i = -1;
	j = 0;
	char_ant = ft_ulltoa_base(nb_ant, 10);
	res = ft_memalloc(5 + ft_strlen(room) + ft_strlen(char_ant));
	res[0] = 'L';
	while (char_ant[++i])
		res[++j] = char_ant[i];
	res[++j] = '-';
	i = -1;
	while (room[++i])
		res[++j] = room[i];
	ft_memdel((void**)&char_ant);
	return (res);
}

void realloc_res(t_env *env, char *res, int reset, int i)
{
	static unsigned int	taille = 1;
	long unsigned	index;
	long unsigned	j;
	char 	       *tmp;

	if (reset == 1 && (taille = 1))
		env->result[i] = ft_memalloc(400);
	if (reset == 0 && !(index = 0))
	{
		while (env->result[i][index])
			index++;
		index--;
		if ((index + ft_strlen(res) + 1 >= taille * 400) && (j = -1))
		{
			tmp = env->result[i];
			env->result[i] = ft_memalloc(++taille * 400);
			while(tmp[++j])
				env->result[i][j] = tmp[j];
			ft_memdel((void **)tmp);
		}
		j = -1;
		while (res[++j])
			env->result[i][++index] = res[j];
		env->result[i][++index] = ' ';
		ft_memdel((void**)&res);
	}
}

void select_ant(t_path *path, t_room *room, t_env *env, unsigned long i)
{
	if (room->next == env->end && (room->ant || path->room == env->start))
	{
		if (room->ant)
			realloc_res(env, create_string(room->ant, env->end->name), 0, i);
		else
		{
			realloc_res(env, create_string(++env->nb_ants, env->end->name), 0, i);
			--path->nb_ant;
		}
		room->ant = 0;
		env->antleft--;
	}
	if (room->prev == env->start && path->nb_ant > 0 && room->ant == 0)
	{
		realloc_res(env, create_string(++env->nb_ants, room->name), 0, i);
		room->ant = env->nb_ants;
		--path->nb_ant;
	}
	if ((room != env->start) && room->prev->ant)
	{
		realloc_res(env, create_string(room->prev->ant, room->name), 0, i);
		room->ant = room->prev->ant;
		room->prev->ant = 0;
	}
}

void launch_ant(t_env *env)
{
	t_path			*tmp;
	t_room			*room;
	unsigned long	nb_tour;

	nb_tour = -1;
	env->antleft = env->nb_ants;
	env->nb_ants = 0;
	ft_printf("\n");
	while (env->antleft > 0)
	{
		realloc_res(env, "", 1, ++nb_tour);
		tmp = env->paths;
		while (tmp)
		{
			room = tmp->room;
			while(room && (room != env->start || tmp->room == env->start))
			{
				select_ant(tmp, room, env, nb_tour);
				room = room->prev;
			}
			tmp = tmp->prev;
		}
		ft_printf("%s\n", env->result[nb_tour]);
	}
}

static int cnt_max_tour(t_path *tmp, long double value, unsigned long nb_path)
{
	unsigned long max_tour;

	max_tour = 0;
	while (tmp)
	{
		if ((long)((unsigned long)(value / nb_path + 0.5) - tmp->length) > 0)
		{
			env->ant_live++;
			tmp->nb_ant = (unsigned long)(value / nb_path + 0.5) - tmp->length;
			value -= ((unsigned long)(value / nb_path + 0.5));
			if (max_tour < tmp->nb_ant + tmp->length)
				max_tour = tmp->nb_ant + tmp->length;
		}
		else
			value -= tmp->length;
		nb_path--;
		tmp = tmp->prev;
	}
	return(max_tour);
}

void release_ants(t_env *env)
{
	t_path			*tmp;
	long double		value;
	unsigned long	nb_path;
	unsigned long	max_tour;

	max_tour = 0;
	if ((env->paths && env->paths->room) || (env->paths->prev && env->paths->prev->room))
	{
		if (!(env->paths && env->paths->room))
			env->paths = env->paths->prev;
		tmp = env->paths;
		value = env->nb_ants;
		nb_path = 0;
		while (tmp)
		{
			value += tmp->length;
			++nb_path;
			tmp = tmp->prev;
		}
		tmp = env->paths;

		env->result = ft_memalloc(sizeof(char *) * max_tour);
		launch_ant(env);
	}
}
