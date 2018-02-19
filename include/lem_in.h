/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:28:55 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/15 20:49:26 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

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
	unsigned long		ant;
	int					weight;
	int					dead;
	char				lock;
}						t_room;

typedef struct			s_conflit
{
	long				len;
	t_room				*old_room;
	t_room				*miss_direction;
	struct s_conflit	*next;
	struct s_conflit	*prev;
}						t_conflit;

typedef struct			s_path
{
	struct s_room		*room;
	struct s_path		*next;
	struct s_path		*prev;
	unsigned long		length;
	unsigned long		nb_ant;
}						t_path;

typedef struct			s_env
{
	struct s_room		*start;
	struct s_room		*end;
	struct s_path		*paths;
	struct s_room		**rooms;
	long unsigned		ant_live;
	char				**result;
	long				nb_rooms;
	long				nb_ants;
	long				antleft;
	int					dp;
	int					conflict;
}						t_env;

enum { ROOM, TUBE, COMM, START, END };

enum { FALSE, TRUE };

#endif
