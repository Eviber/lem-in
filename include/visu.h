/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:47:24 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/11 09:53:11 by ygaude           ###   ########.fr       */
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
SDL_Texture				*strtotex(char *str, t_winenv env, TTF_Font *f);
t_winenv				*getsdlenv(t_env *colony);
double					dist(double x1, double y1, double x2, double y2);
int						quitvisu(t_winenv *env);

/*
** Events
*/
int						handle_event(t_winenv *env);

int						visu_init(t_env *colony);
int						visu(void);

/*
** visu_put
*/
void				putlast(t_winenv *w, t_env colony);
void				putroomname(t_winenv w, char *roomname, t_pos pos);
void				putroom(t_winenv w, t_room *room, t_env colony);
void				putpipes(SDL_Renderer *render, t_room room, t_winenv w);
void				putcount(t_winenv env, char *str, SDL_Rect *rect);

/*
**	visu_update
*/

void				updatelast(t_winenv *w, t_env colony);
void				visu_update(SDL_Renderer *render, t_env colony, t_winenv *w);

/*
**	visu
*/

void				putant(t_winenv w, t_room *room, t_room *prev, int ant);
void				counter(t_env colony, t_winenv env);
void				cleartex(SDL_Renderer *render, SDL_Texture *tex);
void				visu_putall(SDL_Renderer *render, t_env colony, t_winenv *w);

#endif
