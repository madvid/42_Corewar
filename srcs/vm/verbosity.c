/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:46:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 11:39:02 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		init_verbotab(t_cw *cw, void *ptr, t_arg *a, int flag)
{
	int (*verbotab[6])(t_cw *cw, void *ptr, t_arg *a, int flag);

	verbotab[0] = &vprint_essentials;
	verbotab[1] = &vprint_lives;
	verbotab[2] = &vprint_cycle;
	verbotab[3] = &vprint_op;
	verbotab[4] = &vprint_deaths;
	verbotab[5] = &vprint_pcmv;
	(cw->options->v_lvl & 0b00000100) ? verbotab[3](cw, ptr, a, flag) : flag;
	(cw->options->v_lvl & 0b00000001) && ((t_process*)ptr)->opcode == 1 ?
		verbotab[1](cw, ptr, a, flag) : flag;
	(cw->options->v_lvl & 0b00000010) ? verbotab[2](cw, ptr, a, flag) : flag;
	(cw->options->v_lvl & 0b00010000) ? verbotab[5](cw, ptr, a, flag) : flag;
	return (flag);
}

int		vprint_essentials(t_cw *cw, void *ptr, int flag)
{
	if (cw || ptr)
		return (flag);
	return (flag);
}

void	pcmv_print(t_cw *cw, void *ptr, int flag, int widht)
{
	t_process	*p;
	int			i;

	p = (t_process*)ptr;
	i = -1;
	if (flag > 1 && (p->opcode == 3 || p->opcode == 11))
		while (++i < flag)
			pcmv_print_arg(cw, ptr, i);
	else
		while (++i < widht)
			pcmv_print_arg(cw, ptr, i);
	ft_printf("\n");
}
