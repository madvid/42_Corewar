/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 16:02:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: vm_init_parse_error
** Description:
**	Free the allocated variables of the parsing structure.
** Return:
**	0: in every cases.
*/

int			vm_init_parse_error(int cd_error, t_parse **p)
{
	int		i;

	i = ((int)NB_ERROR_MSG);
	if (cd_error >= 4)
		ft_memdel((void **)&((*p)->id_table));
	if (cd_error >= 3)
	{
		while (--i >= 0)
			ft_strdel(&((*p)->error[i]));
	}
	if (cd_error >= 2)
		ft_memdel((void**)((*p)->error));
	if (cd_error >= 1)
		ft_memdel((void **)p);
	ft_putstr("Memory allocation issue during initialization of the");
	ft_putstr("struct parse.\n");
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
