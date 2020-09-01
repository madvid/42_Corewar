/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaye <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:38:46 by yaye              #+#    #+#             */
/*   Updated: 2019/10/21 11:38:47 by yaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int		gnl_leave(t_list *list, char **buf)
{
	t_list	*p;

	if (list->content)
	{
		ft_memdel((void **)&list->content);
		p = list->next;
		while (p)
		{
			list = p->next;
			ft_memdel((void **)&p->content);
			ft_memdel((void **)&p);
			p = list;
		}
	}
	ft_memdel((void **)buf);
	return (-1);
}

t_list	*get_fd(t_list *list, int fd)
{
	t_list	*ret;

	if (fd == 0 && !list->content)
	{
		if (!(list->content = malloc(sizeof(void))))
			return (NULL);
		list->content = ft_memcpy(list->content, "\0", 1);
		list->content_size = 0;
	}
	ret = list;
	while (ret->next && ret->content_size != (size_t)fd)
		ret = ret->next;
	if (ret->content_size != (size_t)fd)
	{
		ret->next = ft_lstnew("\0", (size_t)fd);
		ret = ret->next;
	}
	return (ret);
}

int		clr_fd(t_list *list, int fd)
{
	t_list	*tmp;
	t_list	*tmp2;

	if (fd == 0)
	{
		ft_memdel((void **)&list->content);
		return (0);
	}
	tmp = list;
	while (tmp && tmp->content_size != (size_t)fd)
		tmp = tmp->next;
	tmp2 = list;
	while (tmp2->next != tmp)
		tmp2 = tmp2->next;
	tmp2->next = tmp->next;
	ft_memdel((void **)&tmp->content);
	ft_memdel((void **)&tmp);
	return (0);
}

char	*gl(t_list *list, int fd, char **old)
{
	char	*line;
	char	*new;
	int		i;

	i = 0;
	while ((*old)[i] && (*old)[i] != '\n')
		i++;
	if (!(line = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = -1;
	while ((*old)[++i] && (*old)[i] != '\n')
		line[i] = (*old)[i];
	line[i] = 0;
	if ((*old)[i] && (*old)[i + 1])
	{
		if (!(new = ft_strsub((*old), i + 1, ft_strlen((*old)) - i - 1)))
			return (NULL);
		ft_memdel((void **)old);
		(*old) = new;
	}
	else
		clr_fd(list, fd);
	return (line);
}

int		get_next_line(const int fd, char **line)
{
	static t_list		list;
	t_list				*current;
	char				*buf;
	char				*new;
	int					rd;

	if (!(buf = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) \
		|| fd < 0 || !line || read(fd, buf, 0) < 0)
		return (gnl_leave(&list, &buf));
	current = get_fd(&list, fd);
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = 0;
		if (!(new = ft_strjoin(current->content, buf)))
			return (gnl_leave(&list, &buf));
		ft_memdel((void **)&current->content);
		current->content = new;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	ft_memdel((void **)&buf);
	if (rd == -1 || !ft_strlen((current->content)))
		return ((rd == -1) ? -1 : clr_fd(&list, fd));
	(*line) = gl(&list, fd, (char **)&current->content);
	return (1);
}
