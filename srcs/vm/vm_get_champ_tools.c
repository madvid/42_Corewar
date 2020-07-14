/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get_champ_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 00:32:42 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/14 18:37:21 by mdavid           ###   ########.fr       */
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

int		get_champ_magic_key(int fd)
{
	int			rd;
	char		*buff;
	uint32_t	max = 0x0;


	if (fd < 0 || read(fd, NULL, 0) < 0	|| !(buff = ft_strnew(4)))
		return (0);
	rd = read(fd, buff, 4);
	max = (buff[3] & 0xff) | ((buff[2] & 0xff) << 8) | ((buff[1] & 0xff) << 16);
	return (max);
}

/*
** Function: get_champ_name
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

// char		*get_champ_name(int fd)
// {

// 	if ()
// 	{

// 	}
// 	else
// 		return (NULL);
// }

/*
** Function: get_champ_comment
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

// char		*get_champ_comment(int fd)
// {
// 	if ()
// 	{

// 	}
// 	else
// 		return (NULL);
// }

/*
** Function: get_champ_bcode
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

// char		*get_champ_bcode(int fd)
// {

// 	if ()
// 	{

// 	}
// 	else
// 		return (NULL);
// }
