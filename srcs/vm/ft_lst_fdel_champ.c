/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_fdel_champ.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:13:40 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/28 13:01:01 by mdavid           ###   ########.fr       */
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

void	ft_lst_fdel_champ(void *link)
{
	if (!link)
		return ;
	((t_champ*)(link))->id = 0;
	((t_champ*)(link))->champ_file = NULL;
	ft_strdel(&(((t_champ*)(link))->name));
	ft_strdel(&(((t_champ*)(link))->comment));
	((t_champ*)(link))->l_bytecode = 0;
	ft_strdel(&(((t_champ*)(link))->bytecode));
	((t_champ*)(link))->mem_pos = 0;
}
