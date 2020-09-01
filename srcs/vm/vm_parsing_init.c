/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:07:10 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/31 20:48:20 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: ft_init_parse_value
** Description:
**	Initialized the values variables of parsing structure variable.
*/

static void	vm_init_parse_value(t_parse *p)
{
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
**	0: if every memory allocations went fine.
**	CODE_ERROR: code of the corresponding error.
*/

static int	vm_init_parse_memalloc(t_parse **p)
{
	if (!(*p = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return ((int)CD_P_STRUCT);
	if (!((*p)->id_available = ft_1d_int_table(MAX_PLAYERS)))
		return ((int)CD_P_IDTAB);
	if (!((*p)->options = (t_options*)ft_memalloc(sizeof(t_options))))
		return ((int)CD_P_OPT);
	return (0);
}

/*
** Function: vm_init_parse
** Description:
**	Initialization of the entire variable structure of parsing:
**		- memory allocation (see vm_init_parse_memalloc),
**		- value initialization (see vm_init_parse_value).
** Return:
**	0: if no error during the initialization of structure parse p.
**	CODE_ERROR: code of the corresponding error.
*/

int			vm_init_parse(t_parse **p)
{
	int		code_error;

	if ((code_error = vm_init_parse_memalloc(p)) != 0)
		return (vm_error_manager(code_error, p, NULL));
	vm_init_parse_value(*p);
	return (0);
}
