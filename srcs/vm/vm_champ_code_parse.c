/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champ_code_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:44:39 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/13 18:51:07 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: get_corewar_magic_key
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

char		*get_corewar_magic_key(char *file)
{

}

/*
** Function: get_champ_name
** Description:
**	[blablabla]
** Return:
**	xxx:
**	NULL:
*/

char		*get_champ_name(char *file)
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

char		*get_champ_comment(char *file)
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

char		*get_champ_bcode(char *file)
{

	if ()
	{

	}
	else
		return (NULL);
}

/*
** Function: vm_champ_code_parse
** Description:
**	Parsing of the champions bytecode, this part couple the parsing and basics
**	tests on the contains of the files.
** Return:
**	1: 
**	0:
*/

int			vm_champ_code_parse(t_list **lst_champs, char **error)
{
	t_list		*xplr;
	t_champ		*ichamp;
	char		*magic_key;

	xplr = *lst_champs;
	while (xplr)
	{
		ichamp = (t_champ*)xplr->cnt;
		magic_key = get_corewar_magic_key(ichamp->champ_file);
		if (!ft_strequ(magic_key, (char*)COREWAR_EXEC_MAGIC))
			return (0); // '0xea83f3' not present at the beginning of the file.
		ichamp->name = get_champ_name(ichamp->champ_file);
		ichamp->comment = get_champ_comment(ichamp->champ_file);
		ichamp->bytecode = get_champ_bcode(ichamp->champ_file);
		if (!(ichamp->name) || !(ichamp->comment) || !(ichamp->bytecode))
			return (vm_error_manager((int)CODE_CHAMP_ERROR, error)); //definir CODE_CHAMP_ERROR et le message associé
		xplr = xplr->next;
	}
}