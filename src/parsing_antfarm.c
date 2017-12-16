/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_antfarm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:10:27 by sbrochar          #+#    #+#             */
/*   Updated: 2017/12/16 01:48:17 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem-in.h>
#include <eparser.h>

static int			get_nb_ants(t_env *antfarm)
{
	int				i;
	char			*nb_ants;

	nb_ants = NULL;
	i = 0;
	get_next_line(0, &nb_ants);
	while (nb_ants && nb_ants[i])
	{
		if (!ft_isdigit(nb_ants[i]))
		{
			ft_strdel(&nb_ants);
			return (FALSE);
		}
		i++;
	}
	antfarm->nb_ants = ft_atoi(nb_ants); // /!\ REPLACE WITH ATOL
	antfarm->antleft = antfarm->nb_ants;
	ft_strdel(&nb_ants);
	return (TRUE);
}

static void			parse_comment(int *start, int *end, char *comment)
{
	if (*comment == '#')
	{
		if (!ft_strcmp(comment + 1, "start"))
			*start = TRUE;
		else if (!ft_strcmp(comment + 1, "end"))
			*end = TRUE;
	}
}

static int			parse_pipe(t_env *antfarm, char *line)
{
	ft_printf("parsing pipe\n", antfarm, line);
	return (FALSE);
}

int					get_antfarm(t_env *antfarm)
{
	char			*line;
	int				rooms;
	int				start;
	int				end;

	line = NULL;
	rooms = TRUE;
	if (!get_nb_ants(antfarm))
		return (FALSE);
	while (get_next_line(0, &line))
	{
		if (line && *line)
		{
			if (*line == '#')
				parse_comment(&start, &end, line + 1);
			else
			{
				if (rooms)
					rooms = parse_room(&start, &end, antfarm, line);
				if (!rooms)
				{
					if (!parse_pipe(antfarm, line))
					{
						ft_strdel(&line);
						return (FALSE);
					}
				}
			}
			ft_strdel(&line);
		}
		else
			break ;
	}
	return (TRUE);
}
