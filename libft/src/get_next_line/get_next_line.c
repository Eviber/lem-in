/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsporer <vsporer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:28:09 by vsporer           #+#    #+#             */
/*   Updated: 2017/02/28 18:13:09 by vsporer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_get_line(const int fd)
{
	char		buff[BUFF_SIZE + 1];
	char		*res;
	char		*tmp;
	int			ret;

	ret = 1;
	res = NULL;
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) && ret != ERROR_VALUE)
	{
		tmp = res;
		res = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
		tmp = NULL;
		if (ft_strchr(buff, '\n'))
			return (res);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	if ((ret && !res) || ret == ERROR_VALUE)
	{
		res = (char*)malloc(sizeof(char));
		*res = -1;
	}
	return (res);
}

char	*gnl_find_endline(char *brutline, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (brutline)
	{
		while (brutline[i] && brutline[i] != '\n' && *brutline != -1)
			i++;
		if (brutline[i] != '\0')
			tmp = ft_strsub(brutline, (i + 1), ((ft_strlen(brutline) - i) - 1));
		*line = ft_strsub(brutline, 0, i);
		ft_strdel(&brutline);
		return (tmp);
	}
	*line = NULL;
	return (tmp);
}

char	*gnl_clean_line(char *brutline, char *begline, char **line)
{
	char	*clean;

	if (brutline && *brutline == -1)
	{
		*line = brutline;
		brutline = NULL;
		return (brutline);
	}
	if (!brutline)
	{
		brutline = begline;
		begline = NULL;
	}
	clean = ft_strjoin(begline, brutline);
	ft_strdel(&brutline);
	ft_strdel(&begline);
	begline = gnl_find_endline(clean, line);
	if (!begline && (!*line || !*line[0]))
		ft_strdel(line);
	return (begline);
}

void	gnl_check_fd(const int fd, char **line)
{
	static t_list	*file;
	t_list			*save;
	char			*beginline;

	save = file;
	while (save)
	{
		if (save->content_size == (size_t)fd)
		{
			save->content = (void*)gnl_clean_line(gnl_get_line(fd),\
			(char*)save->content, line);
			return ;
		}
		save = save->next;
	}
	beginline = gnl_clean_line(gnl_get_line(fd), NULL, line);
	if (**line == -1)
		return ;
	else if (beginline)
		ft_lstadd(&file, ft_lstnew((void*)beginline, ft_strlen(beginline) + 1));
	else
		ft_lstadd(&file, ft_lstnew((void*)beginline, 0));
	file->content_size = (size_t)fd;
	ft_strdel(&beginline);
}

int		get_next_line(const int fd, char **line)
{
	if (fd >= INPUT_FD)
	{
		if (!line)
			return (ERROR_VALUE);
		gnl_check_fd(fd, line);
		if (*line)
		{
			if (**line == -1)
			{
				ft_strdel(line);
				return (ERROR_VALUE);
			}
			else
				return (READ_VALUE);
		}
		else
			return (EOF_VALUE);
	}
	else
		return (ERROR_VALUE);
}
