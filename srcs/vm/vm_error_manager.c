/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/03 13:41:13 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: vm_init_cw_error
** Description:
**	Free the allocated variables of the parsing structure.
** Return:
**	0: in every cases.
*/

int			vm_init_cw_error(int cd_error, t_cw **cw)
{
	if (cd_error >= (int)CD_INI_PROC && (*cw)->process)
		ft_lstdel(&((*cw)->process), &ft_lst_fdel_proc);
	if (cd_error >= CD_ID_ARENA)
		ft_1d_int_tabledel(&((*cw)->id_arena), REG_NUMBER);
	if (cd_error >= CD_ARENA)
		ft_strdel(&((*cw)->arena));
	if (cd_error >= CD_CW_STRUCT)
		ft_memdel((void **)cw);
	return (0);
}

/*
** Function: vm_init_parse_error
** Description:
**	Free the allocated variables of the parsing structure.
** Return:
**	0: in every cases.
*/

int			vm_init_parse_error(int cd_error, t_parse **p)
{
	if (cd_error >= (int)CD_BD_VAL && (*p)->lst_champs)
		ft_lstdel(&((*p)->lst_champs), &ft_lst_fdel_champ);
	if (cd_error >= CD_P_OPT)
		ft_memdel((void**)&((*p)->options));
	if (cd_error >= CD_P_IDTAB)
		ft_memdel((void**)(&((*p)->id_available)));
	if (cd_error >= CD_P_STRUCT)
		ft_memdel((void **)p);
	return (0);
}

/*
** Function: vm_error_manager
** Description:
**	Error messages manager, print the error message depending of it code_error.
** Return:
**	0: in every cases, it transmit the error signal (0).
*/

int			vm_error_manager(int code_error, t_parse **p, t_cw **cw)
{
	static	char	*msg[] = {M_USAGE, M_P_STRUCT, M_P_IDTAB, M_P_OPT, M_DUMP,
						M_VERB, M_MUSIC, M_UNIQ, M_BD_VAL, M_BD_FILE, M_DUPL_N,
						M_FILE_BIG, M_MEM_CHAMP, M_EMPTY_CHP, M_MAX_CHAMP,
						M_INV_FD, M_MAGIC_EXEC, M_CHP_ERR, M_SORT_CHP,
						M_PROC_MEM, M_CW_STRUCT, M_ARENA, M_ID_ARENA,
						M_INI_PROC, M_FORK, M_FIN, NULL};

	if (code_error != FIN_DU_GAME)
	{
		write(2, msg[code_error], ft_strlen(msg[code_error]));
		write(2, "\n", 1);
	}
	if (p)
		vm_init_parse_error(code_error, p);
	if (cw)
		vm_init_cw_error(code_error, cw);
	if (code_error != CD_USAGE && code_error != FIN_DU_GAME)
	{
		write(2, "Remainder:\n########################\n", 36);
		write(2, msg[CD_USAGE], ft_strlen(msg[CD_USAGE]));
		write(2, "\n########################\n", 26);
	}
	return (code_error);
}
