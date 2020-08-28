/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_fdel_proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:42:44 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/28 12:28:03 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: ft_lst_fdel_champ
** Description:
**	Specific function to delete the list of champions in Corewar project (42
**	Paris).
*/

void	ft_lst_fdel_proc(void *proc)
{
	if (!proc)
		return ;
	((t_process*)(proc))->id = 0;
	((t_process*)(proc))->carry = 0;
	((t_process*)(proc))->opcode = 0;
	((t_process*)(proc))->n_lives = 0;
	((t_process*)(proc))->wait_cycles = 0;
	((t_process*)(proc))->i = 0;
	((t_process*)(proc))->pc = 0;
	((t_process*)(proc))->champ = NULL;
	free(((t_process*)(proc))->registers);
}
