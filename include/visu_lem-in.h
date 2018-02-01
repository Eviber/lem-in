/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_lem-in.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 16:15:42 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/31 15:37:37 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_LEM_IN_H
# define VISU_LEM_IN_H

# include <SDL2/SDL.h>
# include <SDL2/SDL2_gfxPrimitives.h>
# include <SDL2/SDL_ttf.h>
# include "libft.h"

# define MULT 0
# define DIV 1
# define ZOOM_MAX 1000

typedef struct		s_visu
{
	int				zoom;
	int				nb_rooms;
	int				i;
	t_room			**rooms;
	t_room			*start;
	t_room			*end;
	t_pos			max;
	t_pos			min;
	t_pos			screen;
	t_pos			origin;
	t_pos			morigin;
	t_pos			offset;
	t_pos			*pos;
	const Uint8		*kb_state;
	TTF_Font		*font;
	SDL_Color		txt_c;
	SDL_Texture		*help;
	SDL_Texture		*step;
	char			**step_list;
	SDL_Rect		step_size;
	SDL_Rect		step_focus;
	SDL_Rect		step_select;
}					t_visu;
/*
** Visu
*/
int		help_display_init(SDL_Renderer *render, t_visu *venv);
int		step_display_init(SDL_Renderer *render, t_visu *venv);
int		get_room_index(t_room **rooms, t_room *src);
int		display_ants(SDL_Renderer *render, t_visu *venv);
int		get_rooms_name(SDL_Renderer *render, int *room, t_visu *venv);
int		event_manager(SDL_Renderer *render, t_visu *venv);
int		draw_anthill(SDL_Renderer *render, t_room **rooms, t_visu *venv);
void	lem_in_visu(t_env *env);
void	reset_pos_map(t_visu *venv);
void	move_step(t_visu *venv);
void	get_default_zoom(t_room **rooms, t_visu *venv);
t_room	*search_room(char *name, t_room **room);

#endif
