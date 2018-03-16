/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:37:57 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/16 17:46:36 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 512
# define READ_VALUE 1
# define EOF_VALUE 0
# define ERROR_VALUE -1

typedef struct		s_gnl_mem
{
	t_list			*list_fd;
	t_list			*current_fd;
	char			**line;
}					t_gnl_mem;

int		get_next_line(const int fd, char **line);

#endif
