/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:28:55 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/12 14:05:56 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_room
{
	struct s_room	**pipes;
	struct s_room	*next;
	struct s_room	*prev;
	char			*name;
	struct s_pos	pos;
	long			ant;
	int				weight;
	int				dead;
	int				locked;
}					t_room;

typedef struct		s_conflict
{
	t_room				*old_room;
	t_room				*miss_direction;
	struct s_conflict	*next;
	struct s_conflict	*prev;
	long				len;
}					t_conflict;

typedef struct		s_path
{
	struct s_room	*room;
	struct s_room	*start;
	int				tosend;
	int				length;
}					t_path;

typedef struct		s_env
{
	struct s_room	*start;
	struct s_room	*end;
	struct s_path	**paths;
	struct s_room	**rooms;
	long			nb_rooms;
	long			nb_ants;
	long			antleft;
	long			lem_out;
	int				depth;
	int				conflict;
	char			*to_print;
}					t_env;

enum { ROOM, TUBE, COMM, START, END };

enum { FALSE, TRUE };

#endif
