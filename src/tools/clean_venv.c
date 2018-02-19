/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_venv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:22:46 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/12 17:37:12 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "parser_lem_in.h"
#include "visu_lem_in.h"

void	clean_venv(SDL_Window *win, SDL_Renderer *render, t_visu *venv)
{
	ft_memdel((void**)&venv->pos);
	if (venv->font)
		TTF_CloseFont(venv->font);
	if (venv->help)
		SDL_DestroyTexture(venv->help);
	if (venv->step)
		SDL_DestroyTexture(venv->step);
	del_strtab(&venv->step_list);
	if (render)
		SDL_DestroyRenderer(render);
	if (win)
		SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
}
