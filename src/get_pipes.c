/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 02:32:59 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/19 19:30:03 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
#include <eparser.h>

static int			check_errors(t_env *antfarm, char **tab, t_room **room1, t_room **room2)
{
	if (tab && tab[0] && tab[1] && !tab[2])
	{
		*room1 = find_room(antfarm, tab[0]);
		*room2 = find_room(antfarm, tab[1]);
		if (*room1 && *room2)
			return (TRUE);
	}
	return (FALSE);
}

static size_t		get_nb_pipes(t_room *room)
{
	size_t			ret;
	t_room			**pipes;

	ret = 0;
	pipes = room->pipes;
	if (pipes)
	{
		while (pipes[ret])
			ret++;
	}
	return (ret);
}

static void			add_pipe(t_room **room1, t_room **room2)
{
	size_t			nb_pipes1;
	size_t			nb_pipes2;

	nb_pipes1 = get_nb_pipes(*room1);
	nb_pipes2 = get_nb_pipes(*room2);
	(*room1)->pipes = add_room((*room1)->pipes, nb_pipes1);
	(*room1)->pipes[nb_pipes1] = *room2;
	(*room2)->pipes = add_room((*room2)->pipes, nb_pipes2);
	(*room2)->pipes[nb_pipes2] = *room1;
}

int					parse_pipe(t_env *antfarm, char *line)
{
	char			**tab;
	char			*tmp;
	t_room			*room1;
	t_room			*room2;

	room1 = NULL;
	room2 = NULL;
	tmp = ft_strtrim(line);
	if (!tmp)
		return (FALSE);
	tab = ft_strsplit(tmp, '-');
	if (!tab)
		return (FALSE);
	if (!check_errors(antfarm, tab, &room1, &room2))
	{
		free_tab(&tab);
		return (FALSE);
	}
	add_pipe(&room1, &room2);
	free_tab(&tab);
	return (TRUE);
}
