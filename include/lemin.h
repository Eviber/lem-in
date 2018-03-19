/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:28:55 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/19 16:23:06 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

typedef struct			s_pos
{
	int					x;
	int					y;
}						t_pos;

typedef struct			s_room
{
	struct s_room		**pipes;
	struct s_room		*next;
	struct s_room		*prev;
	char				*name;
	struct s_pos		pos;
	long				ant;
	int					weight;
	int					dead;
	int					locked;
	int 				weight_diff;
}						t_room;

typedef struct			s_conflict
{
	long				new_len;
	long				old_len;
	long 				state;
	long 				conflict;
	t_room				*old_room;
	t_room				*missss_direction;
	t_room				*miss_direction;
	struct s_conflict	*next;
	struct s_conflict	*prev;
}						t_conflict;

typedef struct			s_path
{
	struct s_room		*room;
	struct s_room		*start;
	int					tosend;
	int					length;
}						t_path;

typedef struct			s_env
{
	struct s_room		*start;
	struct s_room		*end;
	struct s_path		**paths;
	struct s_room		**rooms;
	struct s_conflict	*conflit;
	char				*to_print;
	unsigned long		mean_len;
	long 				nb_path;
	long				nb_rooms;
	long				nb_ants;
	long				antleft;
	long				lem_out;
	int					depth;
	int					conflict;
	int					v;
}						t_env;

enum { ROOM, TUBE, COMM, START, END };

enum { FALSE, TRUE };

#endif
