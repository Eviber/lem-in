/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_display_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:19:06 by vsporer           #+#    #+#             */
/*   Updated: 2018/01/29 14:44:25 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "visu_lem-in.h"

static int		create_help_msg(SDL_Renderer *render, SDL_Rect *pos, \
TTF_Font *font, char *msg)
{
	SDL_Texture		*text;
	SDL_Color		color;
	SDL_Surface		*surf;

	color.r = 200;
	color.g = 200;
	color.b = 200;
	color.a = 255;
	if (!(surf = TTF_RenderText_Solid(font, msg, color)))
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

static int		create_main_texture(SDL_Renderer *render, t_visu *venv)
{
	if (!(venv->help = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, \
	SDL_TEXTUREACCESS_TARGET, 389, 400)))
		return (1);
	if (SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND))
		return (1);
	if (SDL_SetTextureBlendMode(venv->help, SDL_BLENDMODE_BLEND))
		return (1);
	if (SDL_SetRenderTarget(render, venv->help))
		return (1);
	SDL_RenderClear(render);
	if (SDL_SetRenderDrawColor(render, 0, 0, 0, 160))
		return (1);
	if (SDL_RenderFillRect(render, NULL))
		return (1);
	return (0);
}

static void		create_msg_tab(char ***msgtab)
{
	if ((*msgtab = (char**)ft_memalloc(sizeof(char*) * 8)))
	{
		(*msgtab)[0] = ft_strdup("Help");
		(*msgtab)[1] = ft_strdup("Move with arrow keys");
		(*msgtab)[2] = ft_strdup("Zoom with '-' and '+' keys");
		(*msgtab)[3] = ft_strdup("Center map with 'space' key");
		(*msgtab)[4] = ft_strdup("Move in step-list with 'j' and 'k' keys");
		(*msgtab)[5] = ft_strdup("Show/Hid step-list press 's' key");
		(*msgtab)[6] = ft_strdup("Show/Hid room's name press 'r' key");
		(*msgtab)[7] = NULL;
	}
}

int				help_display_init(SDL_Renderer *render, t_visu *venv)
{
	SDL_Rect		pos;
	char			**msgtab;
	int				i;

	i = -1;
	if (create_main_texture(render, venv))
		return (1);
	create_msg_tab(&msgtab);
	while (msgtab && msgtab[++i])
	{
		if (!i)
			pos.x = 389 / 2 - 20;
		else
			pos.x = 20;
		pos.y = 30 * (i * 2);
		if (create_help_msg(render, &pos, venv->font, msgtab[i]))
			return (1);
		ft_strdel(&msgtab[i]);
	}
	ft_memdel((void**)&(msgtab));
	if (SDL_SetRenderTarget(render, NULL))
		return (1);
	return (0);
}
