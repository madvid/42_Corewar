/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_champ_code_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 17:44:39 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 02:02:49 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "vm.h"

/*
** Function: vm_champ_file_parse
** Description:
**	[put some description here]
** Return:
**	1:	success in getting magic_key, name, comment and bytecode
**		of the current champion.
**	0: otherwise
*/

static int		vm_champ_file_parse(t_champ *ichamp, char **error)
{
	int			magic_key;
	int			fd;

	fd = open(ichamp->champ_file, O_RDONLY);
	magic_key = get_champ_magic_key(fd);
	if ( magic_key - (int)(COREWAR_EXEC_MAGIC) != 0)
		return (0); // '0xea83f3' not present at the beginning of the file.
	ichamp->name = get_champ_name(fd);
	ichamp->l_bytecode = get_champ_l_bcode(fd);
	ichamp->comment = get_champ_comment(fd, ichamp->l_bytecode);
	// ichamp->bytecode = get_champ_bcode(fd);
	close(fd);
	if (!(ichamp->name) || !(ichamp->comment) || !(ichamp->bytecode))
		return (vm_error_manager((int)CD_CHP_ERR, error)); //definir CODE_CHAMP_ERROR et le message associé
	return (1);
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

int			vm_champ_parse(t_list **lst_champs, char **error)
{
	t_list		*xplr;
	t_champ		*ichamp;

	xplr = *lst_champs;
	while (xplr)
	{
		ichamp = (t_champ*)xplr->cnt;
		vm_champ_file_parse(ichamp, error);
		xplr = xplr->next;
	}
	return (1);
}