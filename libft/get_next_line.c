/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 14:16:47 by ygaude            #+#    #+#             */
/*   Updated: 2017/09/20 18:03:29 by ygaude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "libft.h"

static char	*getbuf(const int fd, int delplz)
{
	static t_list	*catalog = NULL;
	t_list			*cur;
	char			*res;

	if (!catalog)
		if (!(catalog = (t_list *)ft_memalloc(sizeof(t_list))))
			return (NULL);
	cur = catalog;
	while (cur->content_size != (size_t)fd && cur->next)
		cur = cur->next;
	if (cur->content_size != (size_t)fd && !delplz)
	{
		if (!(res = ft_strnew(BUFF_SIZE)))
			return (NULL);
		ft_lstaddend(&catalog, ft_lstnew((const void *)res, BUFF_SIZE + 1));
		ft_strdel(&res);
		cur = cur->next;
		cur->content_size = (size_t)fd;
	}
	if (cur->content_size == (size_t)fd && delplz)
		ft_memdel(&(cur->content));
	res = (cur) ? (char *)cur->content : NULL;
	return (res);
}

int			get_next_line(const int fd, char **line)
{
	char				*buf;
	char				*tmp;
	ssize_t				ret;

	ret = 1;
	buf = getbuf(fd + 1, 0);
	if (!buf || !line || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = NULL;
	tmp = ft_strdup(buf);
	while (tmp && !ft_strchr(tmp, '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strappend(&tmp, &buf, 'F');
	}
	if ((!tmp || ret == -1) || !(*line = ft_strsub(tmp, 0, (ft_strchr(tmp,
		'\n')) ? ((size_t)(ft_strchr(tmp, '\n') - tmp)) : ft_strlen(tmp))))
		return (-1);
	ft_strclr(buf);
	if (ft_strchr(tmp, '\n'))
		ft_strcpy(buf, (ft_strchr(tmp, '\n') + 1));
	ft_strdel(&tmp);
	if (!(ret || ft_strlen(buf) || ft_strlen(*line)))
		getbuf(fd + 1, 1);
	return ((ret || ft_strlen(buf) || ft_strlen(*line)) ? 1 : 0);
}
