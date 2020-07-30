/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:25:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/30 14:30:04 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	copy_options(t_cw *cw, t_parse *p)
{
	cw->options.dump = p->options->dump;
	cw->options.dump_cycle = p->options->dump_cycle;
	cw->options.aff = p->options->aff;
}