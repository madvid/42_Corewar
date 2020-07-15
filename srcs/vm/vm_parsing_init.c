/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:07:10 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 18:27:13 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: ft_init_parse_value
** Description:
**	Initialized the values variables of parsing structure variable.
*/

static void		vm_init_parse_value(t_parse *p)
{
	int			i;

	i = -1;
	p->nb_champ = 0;
	p->id_champ = 0;
	p->options->dump = 0;
	p->options->nbr_cycle = 0;
	p->options->n = 0;
	p->lst_champs = NULL;
	while (++i < 4)
		p->id_table[i] = 0;
}

/*
** Function: ft_init_parse_value
** Description:
**	Does all the allocation memory of the variables within the parsing struc
**	variable p:
**		- p itself,
**		- p->error and error[i],
**		- p->id_table,
** Return:
**	1: if every memory allocations went fine.
**	0: otherwise.
*/

static int		vm_init_parse_memalloc(t_parse **p)
{
	int				i;
	static	char	*msg[] = {M_USAGE, M_DUMP, M_BD_VAL, M_BD_CHAMP_NB,
						M_MEM_CHAMP, M_EMPTY_CHP, M_MAX_CHAMP,
						M_BD_CODE, M_CHP_ERR, M_INV_FD, M_MAGIC_EXEC, NULL};

	i = 0;
	if (!(*p = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (vm_init_parse_error(0, p));
	if (!((*p)->error = (char**)ft_memalloc(sizeof(char*) * (int)NB_ERROR_MSG)))
		return (vm_init_parse_error(1, p));
	while (i < (int)NB_ERROR_MSG)
	{
		if (!((*p)->error[i] = ft_strdup(msg[i])))
		{
			ft_strtabldel(&((*p)->error));
			return (vm_init_parse_error(2, p));
		}
		i++;
	}
	if (!((*p)->id_table = (int *)ft_memalloc(sizeof(int) * MAX_PLAYERS)))
		return (vm_init_parse_error(3, p));
	if (!((*p)->options = (t_options*)ft_memalloc(sizeof(t_options))))
		return (vm_init_parse_error(4, p));
	return (1);
}

/*
** Function: vm_init_parse
** Description:
**	Initialization of the entire variable structure of parsing:
**		- memory allocation (see vm_init_parse_memalloc),
**		- value initialization (see vm_init_parse_value).
** Return:
**	1: if any memory allocation issue showed up in vm_init_parse_memalloc.
**	0: otherwise.
*/

int				vm_init_parse(t_parse **p)
{
	if (!vm_init_parse_memalloc(p))
		return (0);
	vm_init_parse_value(*p);
	return (1);
}
