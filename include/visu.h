/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:47:24 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/09 13:36:55 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL_ttf.h>
# include "lemin.h"

# define TURNTIME 1000
# define TARGET SDL_TEXTUREACCESS_TARGET

enum { TUBES, ROOMS, ANTS, ANT };

typedef struct			s_winenv
{
	SDL_DisplayMode		dispmode;
	SDL_Window			*win;
	SDL_Renderer		*render;
	SDL_Texture			*layer[4];
	struct s_room		**rooms;
	struct s_env		*colony;
	size_t				*lastants;
	TTF_Font			*bigfont;
	TTF_Font			*font;
	struct s_pos		mov;
	double				zoom;
	double				orig_zoom;
	Uint32				ticks;
	Uint32				frameticks;
	Uint32				offticks;
	int					putnames;
	int					quit;
	unsigned int		turntime;
	unsigned int		wait;
}						t_winenv;

/*
** Utilities
*/
int						panic(const char *str, const char *str2);
SDL_Texture				*strtotex(char *str, t_winenv env, SDL_Color color);
t_winenv				*getsdlenv(t_env *colony);
double					dist(double x1, double y1, double x2, double y2);
int						quitvisu(t_winenv *env);

/*
** Events
*/
int						handle_event(t_winenv *env);

int						visu_init(t_env *colony);
int						visu(void);

#endif
