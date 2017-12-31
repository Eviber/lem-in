/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 11:36:50 by vsporer           #+#    #+#             */
/*   Updated: 2016/12/01 15:24:08 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFF_SIZE 128
# define ERROR_VALUE -1
# define READ_VALUE 1
# define EOF_VALUE 0
# define INPUT_FD 0
# define ENDLINE 1
# define CLEANLINE 0

int		get_next_line(const int fd, char **line);

#endif
