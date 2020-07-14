/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_champ_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 00:32:42 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/14 02:44:04 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: get_champ_magic_key
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

char		*get_champ_magic_key(int fd)
{
	int		rd;
	char	*buff;

	if (fd < 0 || read(fd, NULL, 0) < 0	|| !(buff = ft_strnew(2)))
		return (NULL);
	if ((rd = read(fd, buff, 2)) > 0)
		buff[rd] = '\0';
	else
	{
		ft_strdel(&buff);
		return (NULL);
	}
	if (ft_strlen(buff) < 2)
	{
		ft_strdel(&buff);
		return (NULL);
	}
	return (buff);
}

/*
** Function: get_champ_name
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

char		*get_champ_name(int fd)
{

	if ()
	{

	}
	else
		return (NULL);
}

/*
** Function: get_champ_comment
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

char		*get_champ_comment(int fd)
{
	if ()
	{

	}
	else
		return (NULL);
}

/*
** Function: get_champ_bcode
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

char		*get_champ_bcode(int fd)
{

	if ()
	{

	}
	else
		return (NULL);
}