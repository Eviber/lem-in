/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:28:55 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/12 14:07:45 by gcollett         ###   ########.fr       */
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
	long				new_len;
	long				old_len;
	long 				state;
	long 				conflict;
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
	struct s_conflit	*conflit;
	long unsigned		ant_live;
	char				**result;
	unsigned long mean_len;
	long 				nb_path;
	long				nb_rooms;
	long				nb_ants;
	long				antleft;
	int					dp;
	int					conflict;
}						t_env;

enum { FALSE, TRUE };

#endif
