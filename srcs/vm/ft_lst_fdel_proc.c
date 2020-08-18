/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_fdel_proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:42:44 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/17 10:57:21 by mdavid           ###   ########.fr       */
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

void	ft_lst_fdel_proc(void *link, size_t link_size)
{
	if (!link || link_size == 0)
		return ;
	if ((t_list*)link && ((t_list*)link)->cnt)
	{
		((t_process*)(((t_list*)link)->cnt))->id = 0;
		((t_process*)(((t_list*)link)->cnt))->carry = 0;
		((t_process*)(((t_list*)link)->cnt))->opcode = 0;
		((t_process*)(((t_list*)link)->cnt))->n_lives = 0;
		((t_process*)(((t_list*)link)->cnt))->wait_cycles = 0;
		((t_process*)(((t_list*)link)->cnt))->i = 0;
		((t_process*)(((t_list*)link)->cnt))->pc = 0;
		((t_process*)(((t_list*)link)->cnt))->champ = NULL;
		ft_1d_int_tabledel(&(((t_process*)(((t_list*)link)->cnt))->registers),
			REG_NUMBER);
	}
	((t_list*)link)->file_d = 0;
	((t_list*)link)->cnt_s = 0;
	((t_list*)link)->next = NULL;
}
