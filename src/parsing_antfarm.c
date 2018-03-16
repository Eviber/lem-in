/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_antfarm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:10:27 by sbrochar          #+#    #+#             */
/*   Updated: 2018/02/08 15:29:41 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>
#include <eparser.h>

static int			get_nb_ants(t_env *antfarm, char *nb_ants, int *ants)
{
	int				i;

	i = 0;
	*ants = FALSE;
	if (nb_ants)
	{
		while (nb_ants[i])
		{
			if (!ft_isdigit(nb_ants[i]))
				return (FALSE);
			i++;
		}
		antfarm->nb_ants = ft_atoi(nb_ants); // /!\ REPLACE WITH ATOL
		antfarm->antleft = antfarm->nb_ants;
	}
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

static int			get_antfarm(t_env *antfarm, char *line, int *start,
					int *end)
{
	static int		rooms = TRUE;
	static int		ants = TRUE;

	if (*line == '#')
		parse_comment(start, end, line + 1);
	else if (ants)
		return (get_nb_ants(antfarm, line, &ants));
	else
	{
		if (rooms)
			rooms = parse_room(start, end, antfarm, line);
		if (!rooms)
		{
			if (!parse_pipe(antfarm, line))
				return (FALSE);
		}
	}
	return (TRUE);
}

static void			register_antfarm(t_env *antfarm, char *line)
{
	static int		first_line = TRUE;
	char			*tmp;

	if (first_line)
	{
		first_line = FALSE;
		antfarm->to_print = ft_strdup(line);
	}
	else
	{
		tmp = ft_strcjoin(antfarm->to_print, line, '\n');
		ft_strdel(&(antfarm->to_print));
		antfarm->to_print = tmp;
	}
}

int					parse_antfarm(t_env *antfarm)
{
	char			*line;
	int				gnl_ret;
	int				start;
	int				end;

	line = NULL;
	start = FALSE;
	end = FALSE;
	while ((gnl_ret = get_next_line(0, &line)) > 0)
	{
		if (line && *line)
		{
			if (!get_antfarm(antfarm, line, &start, &end))
			{
				ft_strdel(&line);
				break ;
			}
			register_antfarm(antfarm, line);
			ft_strdel(&line);
		}
		else
			break ;
	}
	ft_strdel(&line);
	if (gnl_ret == -1 || !((antfarm->nb_ants > -1) && antfarm->start && antfarm->end))
		return (FALSE);
	return (TRUE);
}
