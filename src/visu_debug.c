/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 12:00:45 by ygaude            #+#    #+#             */
/*   Updated: 2018/03/14 14:22:30 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		visu_debug(int state)
{
	t_winenv	*w;

	w = getsdlenv(NULL);
	w->debug = state;
	w->redraw = 1;
}