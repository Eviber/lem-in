/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 22:47:24 by ygaude            #+#    #+#             */
/*   Updated: 2017/12/16 19:36:05 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <SDL.h>
# include <SDL_ttf.h>
# include "lem-in.h"

typedef struct			s_winenv
{
	SDL_DisplayMode		dispmode;
	SDL_Window			*win;
	SDL_Renderer		*render;
	struct s_room		**rooms;
	struct s_env		*colony;
	struct s_pos		mov;
	unsigned int		zoom;
}						t_winenv;

#endif
