/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 12:37:23 by mdavid           ###   ########.fr       */
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
	{
		while (xplr)
		{
			free(((t_process*)(xplr->cnt))->registers);	// Faudra tester que l'on libere bien toute la memoire
			((t_process*)(xplr->cnt))->registers = NULL;
			xplr = xplr->next;						// et qu'on oubli pas de free quelque chose.
		}
	}
	if (cd_error >= 3)
	{
		ft_lstdel(&((*cw)->process), ft_lst_fdel);	// Faudra tester que l'on libere bien toute la memoire
		(*cw)->process = NULL;						// et qu'on oubli pas de free quelque chose.
	}
	// if (cd_error >= xx)
	// 	free((*cw)->id_arena));
	if (cd_error >= 2)
		ft_strdel(&((*cw)->arena));
	if (cd_error >= 1)
		ft_memdel((void **)cw);
	if (cd_error <= 4)
		ft_putendl("Memory allocation failed \
		during initialization of struct cw.");
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
	if (cd_error >= 3)
		ft_memdel((void**)&((*p)->options));
	if (cd_error >= 2)
		ft_memdel((void**)((*p)->id_table));
	if (cd_error >= 1)
		ft_memdel((void **)p);
	if (cd_error <= 3)
		ft_putstr("Memory allocation failed for parsing structure t_strut p\n");
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
	static	char	*msg[] = {M_USAGE, M_DUMP, M_BD_VAL, M_BD_CHAMP_NB,
						M_MEM_CHAMP, M_EMPTY_CHP, M_MAX_CHAMP,
						M_BD_CODE, M_CHP_ERR, M_INV_FD, M_MAGIC_EXEC,
						M_VERB, M_UNIQ, NULL};

	ft_putendl(msg[code_error]);
	if (code_error != CD_USAGE)
		ft_putendl(msg[CD_USAGE]);
	if (p)
		vm_init_parse_error(4, p);
	if (cw)
		vm_init_cw_error(5, cw);

	return (0);
}
