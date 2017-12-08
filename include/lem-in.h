/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:28:55 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/05 10:04:14 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct		s_room
{
	struct s_room	*links;
	char			*name;
	int				nlinks;
	char			full;
}					t_room;

typedef struct		s_ant
{
	struct s_room	*room;
	int				id;
}					t_ant;

typedef struct		s_env
{
	struct s_room	*start;
	struct s_room	*end;
	struct s_ant	*ants;
	int				atstart;
}					t_env;

enum { ROOM, TUBE, COMM, START, END };

#endif
