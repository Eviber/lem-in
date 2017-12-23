/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cookielem-in.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourmea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 20:32:03 by pbourmea          #+#    #+#             */
/*   Updated: 2017/12/22 20:32:08 by pbourmea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOKIELEM_IN_H
# define COOKIELEM_IN_H

# include "libft.h"
# include <stdio.h>
# include <sys/types.h>
# define ERR_READ "error while reading stdin\n"
# define ERR_DIGIT "error while checking digit format\n"
# define ERR_ALLOC "error while allocating memory\n"
# define TRUE 1
# define FALSE 0

enum { NO_ANT, ANT, START, END };
enum { ROOM, TUBE, ERROR, LICORNE };

typedef struct	s_tube
{
	struct s_room	*room;
	struct s_tube	*next;
}				t_tube;

typedef struct	s_room
{
	int				x;
	int				y;
	unsigned long	ant;//a changer en unsigned long
	int				weight;
	char			*name;
	t_tube			*tubes;
	t_tube			*a_tube;
	struct s_room	*next;
	struct s_room	*prev;
}				t_room;

typedef struct	s_map
{
	unsigned long	ant;//a changer en unsigned long
	unsigned long	antleft;// voir commentaire du dessus
	unsigned long	nb_rooms;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
	t_tube			*tubes;
	t_room			*tmp[2];
	t_room			*path;
}				t_map;

int				parser(t_map *map);
void			ft_error(unsigned long motif);
void			connect_rooms(t_map *map);
void			room_print(t_room *room);
void			init_room(t_map *map, t_room *room, char **data, int p_status);
int				find_shortest(t_map *map);

#endif
