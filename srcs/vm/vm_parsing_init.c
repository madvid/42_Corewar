/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:07:10 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/25 10:29:23 by mdavid           ###   ########.fr       */
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
	p->options->dump = false;
	p->options->dump_cycle = 0;
	p->options->n = 0;
	p->lst_champs = NULL;
	p->options->aff = false;
	p->options->sdl = false;
	p->options->music = false;
	p->options->verbose = false;
	p->options->v_lvl = 0;
}

/*
** Function: ft_init_parse_value
** Description:
**	Does all the allocation memory of the variables within the parsing struc
**	variable p:
**		- p itself,
**		- p->error and error[i],
**		- p->id_available,
** Return:
**	1: if every memory allocations went fine.
**	0: otherwise.
*/

static int		vm_init_parse_memalloc(t_parse **p)
{
	if (!(*p = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (vm_error_manager(CD_P_STRUCT, p, NULL));
	if (!((*p)->id_available = ft_1d_int_table(MAX_PLAYERS)))
		return (vm_error_manager(CD_P_IDTAB, p, NULL));
	if (!((*p)->options = (t_options*)ft_memalloc(sizeof(t_options))))
		return (vm_error_manager(CD_P_OPT, p, NULL));
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
