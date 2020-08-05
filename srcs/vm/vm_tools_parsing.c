/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:25:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 12:34:14 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	copy_options(t_cw *cw, t_parse *p)
{
	cw->options.dump = p->options->dump;
	cw->options.dump_cycle = p->options->dump_cycle;
	cw->options.aff = p->options->aff;
	cw->options.sdl = p->options->sdl;
	cw->options.verbose = p->options->verbose;
	cw->options.v_lvl = p->options->v_lvl;

}

/*
** Function: is_dump_option
** Description:
**	Function check if the string arg is the option flag -dump. If so, flag for
**	option dump is set to 1 (otherwise 0).
** Return:
**	1: if the str arg is the flag option dump
**	0: if not
*/

int		is_dump_option(char *arg, t_parse *p)
{
	p->options->dump = (ft_strequ(arg, "-dump") == 1) ? 1 : 0;
	return (p->options->dump);
}

/*
** Function: in_verbose_range
** Description:
**	Function checks if the str arg is a positive number or null
**	within 0 and 31 both included.
** Return:
**	1: if arg is in verbose level range
**	0: otherwise
*/

int		in_verbose_range(char *arg)
{
	int		option;

	if (ft_is_positive_int(arg) == -1)
		return (0);
	option = ft_atoi(arg);
	if (!(option >= 0 && option <= 31))
		return (0);
	
	return (1);
}
