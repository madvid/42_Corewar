/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:25:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 11:02:17 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	copy_options(t_cw *cw, t_parse *p)
{
	cw->options.dump = p->options->dump;
	cw->options.dump_cycle = p->options->dump_cycle;
	cw->options.aff = p->options->aff;
	cw->options.v_lvl = p->options->v_lvl;
	cw->options.verbose = p->options->verbose;
}
