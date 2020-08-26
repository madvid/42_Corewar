/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:15:39 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/27 01:31:49 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vprint_lives(t_cw *cw, t_arg a)
{
	t_list	*xplr;

	xplr = cw->lst_champs;
	while (xplr)
	{
		if (a.arg[0] == ((t_champ*)(xplr->cnt))->id)
			ft_printf("Player %d (%s) is said to be alive\n" \
				, ((t_champ*)(xplr->cnt))->id \
				, ((t_champ*)(xplr->cnt))->name);
		xplr = xplr->next;
	}
}

void	vprint_cycle(t_cw *cw, int flag)
{
	if (flag == 0)
		ft_printf("Cycle to die is now %d\n", cw->cycle_to_die);
	if (flag == 1)
		ft_printf("It is now cycle %d\n", cw->tot_cycle);
}

void	vprint_op(t_process *p, t_arg a)
{
	char		*tmp;

	tmp = (!p->carry) ? " OK" : " FAILED";
	if (p->opcode == 12 || p->opcode == 15)
		opcode_v12(p, a);
	else
		opcode_g(p, tmp, a);
	if (p->opcode == 11)
		opcode_v11(p, a);
	if (p->opcode == 10)
		opcode_v10(p, a);
}

void	vprint_deaths(t_cw *cw, t_process *p)
{
	ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
		p->id, cw->i_cycle - p->last_live, cw->cycle_to_die);
}

void	vprint_pcmv(t_cw *cw, t_process *p, t_arg a)
{
	int			j;

	if (p->opcode == 9 && !p->carry)
		return ;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", a.widht, p->i, \
		(p->i + a.widht) % MEM_SIZE);
	j = -1;
	while(++j < a.widht)
		ft_printf("%2.2x ", (unsigned char)cw->arena[(p->i + j) % MEM_SIZE]);
	ft_putchar('\n');
}
