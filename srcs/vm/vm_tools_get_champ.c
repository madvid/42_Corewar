/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_get_champ.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 00:32:42 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/03 16:19:23 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "vm.h"

/*
** Function: get_champ_magic_key
** Description:
**	Reads of the 4 first octets and fill a int variables to return this
**	4 octets which are potentially the COREWAR_EXEC_MAGIC
** Return:
**	magic: the 4 first octets of the file cast into int.
**	0: if wrong file descriptior, not existing file or memory allocation issue
*/

int			get_champ_magic_key(int fd)
{
	int			rd;
	char		*buff;
	int			magic;

	magic = 0;
	if (fd < 0 || read(fd, NULL, 0) < 0 || !(buff = ft_strnew(4)))
		return (0);
	if ((rd = read(fd, buff, 4)) != 4)
	{
		ft_strdel(&buff);
		return (0);
	}
	magic = (buff[3] & 255) | ((buff[2] & 255) << 8) | ((buff[1] & 255) << 16);
	ft_strdel(&buff);
	return (magic);
}

/*
** Function: get_champ_name
** Description:
**	Reads the PROG_NAME_LENGTH octets (check if there is indeed
**	PROG_NAME_LENGTH octets read) and return it.
** Return:
**	buff: The 128 bytes read in the current champion.
**	NULL: if any issue occurs.
*/

char		*get_champ_name(int fd)
{
	int			rd;
	char		*buff;

	if (!(buff = ft_strnew(PROG_NAME_LENGTH)))
		return (NULL);
	if ((rd = read(fd, buff, PROG_NAME_LENGTH)) != PROG_NAME_LENGTH)
	{
		ft_strdel(&buff);
		return (NULL);
	}
	return (buff);
}

/*
** Function: get_champ_lbcode
** Description:
**	Skips the padding of 4 bytes which must be 4 x NULL and reads
**	the length of champion bytecode corresponding to the executable part.
**	The executable part must not exceed CHAMP_MAX_SIZE (=682 bytes).
** Return:
**	l_bcode: The length of champion executable bytecode.
**	0: if any issue occurs.
*/

int			get_champ_l_bcode(int fd)
{
	int			rd;
	char		*buff;
	int			l_bcode;

	if (!(buff = ft_strnew(8)))
		return (0);
	if ((rd = read(fd, buff, 8)) != 8)
	{
		ft_strdel(&buff);
		return (0);
	}
	if (buff[0] || buff[1] || buff[2] || buff[3])
	{
		ft_strdel(&buff);
		return (0);
	}
	l_bcode = (buff[7] & 255) | ((buff[6] & 255) << 8)
		| ((buff[5] & 255) << 16) | ((buff[4] & 255) << 24);
	ft_strdel(&buff);
	return (l_bcode);
}

/*
** Function: get_champ_comment
** Description:
**	Reads the COMMENT_LENGTH bytes (check if there is indeed
**	COMMENT_LENGTH bytes read) and return it.
** Return:
**	buff: The 2048 bytes read in the current champion.
**	NULL: if any issue occurs.
*/

char		*get_champ_comment(int fd)
{
	int			rd;
	char		*buff;

	if (!(buff = ft_strnew(COMMENT_LENGTH)))
		return (NULL);
	if ((rd = read(fd, buff, COMMENT_LENGTH)) != COMMENT_LENGTH)
	{
		ft_strdel(&buff);
		return (NULL);
	}
	return (buff);
}

/*
** Function: get_champ_bcode
** Description:
**	Skips 4 NULL bytes (and check if it's NULL) and reads the
**	l_bytecode following bytes. There must not be any NULL byte.
** Return:
**	buff: bytecode of the champion.
**	NULL: if any issue occurs.
*/

char		*get_champ_bcode(int fd, int l_bcode)
{
	char		*buff1;
	char		*buff2;

	if (!(buff1 = ft_strnew(4)) || (read(fd, buff1, 4) != 4))
	{
		ft_strdel(&buff1);
		return (0);
	}
	if (!(buff2 = ft_strnew(l_bcode)) || (read(fd, buff2, l_bcode) != l_bcode))
	{
		ft_strdel(&buff1);
		ft_strdel(&buff2);
		return (0);
	}
	if (buff1[0] || buff1[1] || buff1[2] || buff1[3])
	{
		ft_strdel(&buff1);
		ft_strdel(&buff2);
		return (0);
	}
	ft_strdel(&buff1);
	return (buff2);
}
