/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:19:06 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/13 01:59:46 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static void		get_texture_tab(SDL_Renderer *render, SDL_Surface **surf, \
t_visu *venv)
{
	int				i;

	i = -1;
	if ((venv->help = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 8)))
	{
		while (surf[++i])
		{
	ft_printf("#######################%d\n", i);
			venv->help[i] = SDL_CreateTextureFromSurface(render, (surf[i]));
			venv->hpos[i].w = surf[i]->w;
			venv->hpos[i].h = surf[i]->h;
			SDL_FreeSurface(surf[i]);
		}
	}
}

static void		create_help_msg(SDL_Renderer *render, t_visu *venv)
{
	int				i;
	SDL_Color		color;
	SDL_Surface		**surf;

	i = -1;
	color.r = 200;
	color.g = 200;
	color.b = 200;
	color.a = 255;
	surf = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 8);
	TTF_SetFontStyle(venv->font, TTF_STYLE_UNDERLINE);
	surf[0] = TTF_RenderText_Blended(venv->font, "Help", color);
	TTF_SetFontStyle(venv->font, TTF_STYLE_NORMAL);
	surf[1] = TTF_RenderText_Blended(venv->font, "Move with:", color);
	surf[2] = TTF_RenderText_Blended(venv->font, "Zoom with:", color);
	surf[3] = TTF_RenderText_Blended(venv->font, "Center map with:", color);
	surf[4] = TTF_RenderText_Blended(venv->font, \
	"Move in step-list with:", color);
	surf[5] = TTF_RenderText_Blended(venv->font, \
	"Show/Hid step-list press:", color);
	surf[6] = TTF_RenderText_Blended(venv->font, \
	"Show/Hid room's name:", color);
	surf[7] = NULL;
	get_texture_tab(render, &(surf[0]), venv);
}

static void		display_msg(SDL_Renderer *render, int frame, t_visu *venv)
{
	int			i;

	i = -1;
	while (venv->help && venv->help[i])
	{
		if (i == 0)
		{
			venv->hpos[i].x = (venv->hpos[i].w / 2 - 100) + frame * 2;
			venv->hpos[i].y = venv->hpos[i].h;
		}
		else
		{
			venv->hpos[i].x = (venv->hpos[i].w / 2 - 180) + frame * 2;
			venv->hpos[i].y = venv->hpos[i].h * i + 10;
		}
		SDL_RenderCopy(render, venv->help[i], NULL, &venv->hpos[i]);
	}
}

void			get_help(SDL_Renderer *render, int *help, t_visu *venv)
{
	static int	frame = 0;

	if (!venv->help)
		create_help_msg(render, venv);
	if (*help == 2 && frame > 0)
		frame--;
	else if (frame < 100)
		frame++;
	else if ((venv->kb_state[SDL_SCANCODE_H] || \
	venv->kb_state[SDL_SCANCODE_F1]) && *help == 1)
		*help = 2;
	if (*help == 2 && frame == 0)
		*help = 0;
	if (frame)
	{
		boxRGBA(render, 0, 0, frame * 2, 300, 0, 0, 0, 150);
		display_msg(render, frame, venv);
	}
}
