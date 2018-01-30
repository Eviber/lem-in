/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:15:42 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/07 19:52:40 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_LEM_IN_H
# define VISU_LEM_IN_H

# include <SDL2/SDL.h>
# include <SDL2/SDL2_gfxPrimitives.h>
# include "libft.h"

# define MULT 0
# define DIV 1

typedef struct		s_visu
{
// int				zoommod;
//	int				bzoom;
	int				zoom;
	t_pos			max;
	t_pos			min;
	t_pos			screen;
	t_pos			origin;
	t_pos			morigin;
	t_pos			offset;
}					t_visu;
/*
** Visu
*/
int		lem_in_visu(t_env *env);
void	get_default_zoom(t_room **rooms, t_visu *venv);
void	get_rooms_visu(SDL_Renderer *render, t_room **rooms, t_visu *venv);
void	get_pipes_visu(SDL_Renderer *render, t_room **rooms, t_visu *venv);
void	event_manager(SDL_Renderer *render, const Uint8 *kb_state, t_visu *venv);

#endif
