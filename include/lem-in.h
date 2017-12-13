/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:28:55 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/13 21:06:55 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_room
{
	struct s_room	**links;
	struct s_room	*next;
	struct s_room	*prev;
	char			*name;
	struct s_pos	pos;
	long			ant;
	int				weight;
}					t_room;

typedef struct		s_path
{
	struct s_room	*room;
	int				length;
}					t_path;

typedef struct		s_env
{
	struct s_room	*start;
	struct s_room	*end;
	struct s_path	**paths;
	long			total_ants;
	long			atstart;
}					t_env;

enum { ROOM, TUBE, COMM, START, END };

#endif
