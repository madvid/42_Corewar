/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 12:40:05 by armajchr          #+#    #+#             */
/*   Updated: 2019/05/13 17:30:25 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_check_error(const int fd, char **line)
{
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	return (0);
}

char	*recupbuff(const int fd, char *dst)
{
	char	buf[BUFF_SIZE + 1];
	int		i;
	char	*tmp;

	while (!ft_strchr(dst, '\n') && ((i = read(fd, buf, BUFF_SIZE))))
	{
		if (i == -1)
			return (NULL);
		buf[i] = '\0';
		if (!(tmp = ft_strjoin(dst, buf)))
			return (NULL);
		ft_strdel(&dst);
		dst = tmp;
	}
	return (dst);
}

int		get_next_line(const int fd, char **line)
{
	int			j;
	static char *dst;
	char		*rest;

	if (ft_check_error(fd, line) == -1)
		return (-1);
	if (!dst)
		if (!(dst = ft_strnew(0)))
			return (-1);
	if ((dst = recupbuff(fd, dst)) == NULL)
		return (-1);
	j = 0;
	while (dst[j] != '\n' && dst[j])
		j++;
	if (!((*line) = ft_strsub(dst, 0, j)))
		return (-1);
	if (dst[0] == '\0' && (*line)[0] == '\0')
		return (0);
	if (!(rest = ft_strdup(*(dst + j) ? dst + j + 1 : dst + j)))
		return (-1);
	ft_strdel(&dst);
	dst = rest;
	if (line && dst)
		return (1);
	return (0);
}
