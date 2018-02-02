/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_venv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:22:46 by vsporer           #+#    #+#             */
/*   Updated: 2018/02/02 16:33:27 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "parser_lem-in.h"
#include "visu_lem-in.h"

void	clean_venv(SDL_Window *win, SDL_Renderer *render, t_visu *venv)
{
	ft_memdel((void**)&venv->pos);
	TTF_CloseFont(venv->font);
	SDL_DestroyTexture(venv->help);
	SDL_DestroyTexture(venv->step);
	del_strtab(&venv->step_list);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
}
