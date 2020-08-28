/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:15:39 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 17:05:00 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vprint_lives(t_cw *cw, void *ptr, t_arg a, int flag)
{
	t_list	*xplr;

	xplr = cw->lst_champs;
	while (xplr && ptr && a.widht)
	{
		if (flag == ((t_champ*)(xplr->cnt))->id)
			ft_printf("Player %d (%s) is said to be alive\n" \
				, ((t_champ*)(xplr->cnt))->id \
				, ((t_champ*)(xplr->cnt))->name);
		xplr = xplr->next;
	}
	return (1);
}

int		vprint_cycle(t_cw *cw, void *ptr, t_arg a, int flag)
{
	if (flag == 1 && !ptr && a.widht)
		ft_printf("Cycle to die is now %d\n", cw->cycle_to_die);
	if (flag == 0 && !ptr && a.widht)
		ft_printf("It is now cycle %d\n", cw->tot_cycle);
	return (flag);
}

int		vprint_op(t_cw *cw, void *ptr, t_arg a, int flag)
{
	char		*tmp;

	tmp = (flag == 1) ? " OK" : " FAILED";
	if (cw)
	{
		if (((t_process*)(ptr))->opcode == 12 || ((t_process*)(ptr))->opcode == 15)
			opcode_v12(ptr, a);
		else
			opcode_g(ptr, tmp, a);
		if (((t_process*)(ptr))->opcode == 11)
			opcode_v11(ptr, a);
		if (((t_process*)(ptr))->opcode == 10)
			opcode_v10(ptr, a);
	}
	return (flag);
}

int		vprint_deaths(t_cw *cw, void *ptr, t_arg a, int flag)
{
	if (flag && a.widht)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
			((t_process*)(ptr))->id, cw->i_cycle - \
			((t_process*)(ptr))->last_live, cw->cycle_to_die);
	return (flag);
}

int		vprint_pcmv(t_cw *cw, void *ptr, t_arg a, int flag)
{
	t_process	*p;
	int			i;

	p = (t_process*)ptr;
	if (cw->options->v_p == 0)
	{
		if (p->opcode == 9 && flag == 1)
			return (flag);
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", a.widht, p->i, \
			(p->i + a.widht) % MEM_SIZE);
		i = -1;
		while (++i < a.widht)
			ft_printf("%.2x ", (unsigned char)cw->arena[(p->i + i) % MEM_SIZE]);
		ft_printf("\n");
	}
	return (flag);
}
