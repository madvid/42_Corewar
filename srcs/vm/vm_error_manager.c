/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/04 14:14:34 by mdavid           ###   ########.fr       */
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
	ft_putstr("Memory allocation issue during initialization of the");
	ft_putstr("struct cw.\n");
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
	if (cd_error >= 2)
		ft_memdel((void**)((*p)->id_table));
	if (cd_error >= 1)
		ft_memdel((void **)p);
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

int			vm_error_manager(int code_error, char **error)
{
	ft_putendl(error[code_error]);
	return (0);
}
