/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_fdel_champ.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:13:40 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/06 16:31:16 by mdavid           ###   ########.fr       */
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

void	ft_lst_fdel_champ(void *link, size_t link_size)
{
	if (!link || link_size == 0)
		return ;
	((t_list*)link)->file_d = 0;
	((t_list*)link)->cnt_s = 0;
	((t_list*)link)->next = NULL;
	if (((t_list*)link)->cnt)
	{
		((t_champ*)(((t_list*)link)->cnt))->id = 0;
		((t_champ*)(((t_list*)link)->cnt))->champ_file = NULL;
		ft_strdel(&(((t_champ*)(((t_list*)link)->cnt))->name));
		ft_strdel(&(((t_champ*)(((t_list*)link)->cnt))->comment));
		((t_champ*)(((t_list*)link)->cnt))->l_bytecode = 0;
		ft_strdel(&(((t_champ*)(((t_list*)link)->cnt))->bytecode));
		((t_champ*)(((t_list*)link)->cnt))->mem_pos = 0;
	}
	free(((t_list*)link)->cnt);
	free(link);
	link = NULL;
}
