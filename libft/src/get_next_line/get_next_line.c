/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:44:43 by vsporer           #+#    #+#             */
/*   Updated: 2018/03/16 17:48:32 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		create_line(char **begin, char **line)
{
	char	*nl;
	size_t	line_size;

	if (!*line)
		return (0);
	line_size = ft_strlen(*line);
	if ((nl = ft_strchr(*line, '\n')) && nl[1] > 0)
	{
		if (!(*begin = ft_strdup(nl + 1)))
			return (ERROR_VALUE);
		line_size = nl - *line;
	}
	else
		line_size = ft_strlen(*line) - 1;
	if (!(nl = ft_strsub(*line, 0, line_size)))
		return (ERROR_VALUE);
	ft_strdel(line);
	*line = nl;
	return (0);
}

static int		read_line(const int fd, t_gnl_mem *memory)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;

	ret = 1;
	ft_bzero((void*)buff, BUFF_SIZE + 1);
	if (memory->current_fd)
	{
		*(memory->line) = (char*)memory->current_fd->content;
		memory->current_fd->content = NULL;
	}
	while (!ft_strchr(*(memory->line), '\n') && \
	(ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (!(*(memory->line) = ft_strjoin_free(*(memory->line), buff, 1)))
			return (ERROR_VALUE);
		ft_bzero((void*)buff, BUFF_SIZE + 1);
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl_mem	memory = {NULL, NULL, NULL};
	t_list				*tmp;

	if (fd >= 0 && line)
	{
		*line = NULL;
		memory.line = line;
		memory.current_fd = memory.list_fd;
		while (memory.current_fd && (int)memory.current_fd->content_size != fd)
			memory.current_fd = memory.current_fd->next;
		if (!memory.current_fd)
		{
			if (!(tmp = ft_lstnew(NULL, 0)))
				return (ERROR_VALUE);
			ft_lstadd(&memory.list_fd, tmp);
			tmp->content_size = (size_t)fd;
			memory.current_fd = tmp;
		}
		if (read_line(fd, &memory) >= 0 && \
		!create_line((char**)&(memory.current_fd->content), line))
			return ((!*line ? EOF_VALUE : READ_VALUE));
	}
	return (ERROR_VALUE);
}
