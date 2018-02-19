/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_display_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:50:15 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/12 16:54:41 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "visu_lem_in.h"

static int		create_base(SDL_Renderer *render, t_visu *venv)
{
	if (venv->step_size.w > 16383)
		venv->step_size.w = 16383;
	if (venv->step_size.h > 16383)
		venv->step_size.h = 16383;
	if (!(venv->step = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, \
	SDL_TEXTUREACCESS_TARGET, venv->step_size.w, venv->step_size.h)))
		return (1);
	if (SDL_SetTextureBlendMode(venv->step, SDL_BLENDMODE_ADD))
		return (1);
	if (SDL_SetRenderTarget(render, venv->step))
		return (1);
	SDL_RenderClear(render);
	if (SDL_SetRenderDrawColor(render, 255, 255, 255, 0))
		return (1);
	if (SDL_RenderFillRect(render, NULL))
		return (1);
	return (0);
}

static int		create_main_texture(SDL_Renderer *render, t_visu *venv)
{
	int				i;
	int				max;
	SDL_Surface		*surf;

	max = 0;
	i = -1;
	while (venv->step_list[++i])
	{
		if (!(surf = TTF_RenderText_Solid(venv->font, venv->step_list[i], \
		venv->txt_c)))
			return (1);
		if (surf->w > max)
			max = surf->w;
		SDL_FreeSurface(surf);
	}
	venv->step_size.y = 0;
	venv->step_size.w = max + 30 < venv->screen.x / 4 ? venv->screen.x / 4 : \
	max + 30;
	venv->step_size.h = surf->h * i * 2;
	if (create_base(render, venv))
		return (1);
	return (0);
}

static int		create_step_line(SDL_Renderer *render, int i, SDL_Rect *pos, \
t_visu *venv)
{
	SDL_Texture		*text;
	SDL_Color		color;
	SDL_Surface		*surf;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	if (!(surf = TTF_RenderText_Solid(venv->font, venv->step_list[i], color)))
		return (1);
	if (!(text = SDL_CreateTextureFromSurface(render, surf)))
		return (1);
	pos->w = surf->w;
	pos->h = surf->h;
	SDL_FreeSurface(surf);
	if (SDL_RenderCopy(render, text, NULL, pos))
		return (1);
	SDL_DestroyTexture(text);
	return (0);
}

int				step_display_init(SDL_Renderer *render, t_visu *venv)
{
	int			i;
	SDL_Rect	pos;

	i = -1;
	if (create_main_texture(render, venv))
		return (1);
	while (venv->step_list[++i])
	{
		pos.x = 0;
		pos.y = 25 + i * 50;
		if (create_step_line(render, i, &pos, venv))
			return (1);
	}
	SDL_SetRenderTarget(render, NULL);
	venv->step_select.y = 25;
	venv->step_select.h = 34;
	return (0);
}
