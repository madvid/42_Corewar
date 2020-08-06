/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/06 16:45:03 by mdavid           ###   ########.fr       */
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
	t_list	*xplr;

	xplr = (*cw)->process;
	if (cd_error >= 4)
		while (xplr)
		{
			free(((t_process*)(xplr->cnt))->registers);	// Faudra tester que l'on libere bien toute la memoire
			((t_process*)(xplr->cnt))->registers = NULL;
			xplr = xplr->next;						// et qu'on oubli pas de free quelque chose.
		}
	if (cd_error >= 3)
	{
		ft_lstdel(&((*cw)->process), ft_lst_fdel);	// Faudra tester que l'on libere bien toute la memoire
		(*cw)->process = NULL;						// et qu'on oubli pas de free quelque chose.
	}
	cd_error >= 2 ? ft_strdel(&((*cw)->arena)) : 0;
	cd_error >= 1 ? ft_memdel((void **)cw) : 0;
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
	static	char	*msg[] = {M_USAGE, M_P_STRUCT, M_P_IDTAB, M_P_OPT,M_DUMP,
						M_VERB, M_UNIQ, M_BD_VAL, M_BD_FILE, M_FILE_BIG,
						M_MEM_CHAMP, M_EMPTY_CHP, M_MAX_CHAMP, M_INV_FD,
						M_BD_CODE, M_CHP_ERR, M_MAGIC_EXEC, NULL};

	ft_putendl(msg[code_error]);
	if (p)
		vm_init_parse_error(code_error, p);
	if (cw)
		vm_init_cw_error(code_error, cw);
	if (code_error != CD_USAGE)
	{
		ft_putendl("Remainder:\n########################");
		ft_putendl(msg[CD_USAGE]);
		ft_putendl("########################");
	}
	return (0);
}
