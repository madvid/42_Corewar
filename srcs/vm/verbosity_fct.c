/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:15:39 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/14 15:42:48 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vprint_lives(t_cw *cw, void *ptr, int flag)
{
	t_list	*xplr;

	xplr = cw->lst_champs;
	while (xplr && ptr)
	{
		if (flag == ((t_champ*)(xplr->cnt))->id)
			ft_printf("Player %d (%s) is said to be alive\n", \
				((t_champ*)(xplr->cnt))->id, \
				((t_champ*)(xplr->cnt))->name);
		xplr = xplr->next;
	}
	return (1);
}

int		vprint_cycle(t_cw *cw, void *ptr, int flag)
{
	if (flag == 1 && !ptr)
		ft_printf("Cycle to die is now %d\n", cw->cycle_to_die);
	if (flag == 0 && !ptr)
		ft_printf("It is now cycle %d\n", cw->tot_cycle);
	return (flag);
}

int		vprint_op(t_cw *cw, void *ptr, int flag)
{
	extern t_op op_tab[17];
	char		*a;
	char		*b;
	char		*tmp;
	char		**arg;

	tmp = (flag == 1) ? "OK" : "FAILED";
	if (cw)
	{
		ft_printf("P\t%d | %s %s %s\n", ((t_process*)(ptr))->id, \
				op_tab[((t_process*)(ptr))->opcode - 1].name, \
				args_to_str(cw, ((t_process*)(ptr))), tmp);
		if (((t_process*)(ptr))->opcode == 11)
		{
			arg = ft_strsplit(args_to_str(cw, ((t_process*)(ptr))), 32);
			a = arg[1];
			b = arg[2];
			ft_printf("\t  |-> store to %s + %s (with pc and mod)\n", a, b);
		}
		return (flag);
	}
	return (flag);
}

int		vprint_deaths(t_cw *cw, void *ptr, int flag)
{
	if (flag)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
				((t_process*)(ptr))->id, cw->i_cycle, cw->cycle_to_die);
	return (flag);
}

int		vprint_pcmv(t_cw *cw, void *ptr, int flag)
{
	extern t_op op_tab[17];
	int			widht;
	int			i;
	char		*tmp;

	widht = instruction_width(cw->arena[((t_process*)(ptr))->opcode + 1 \
			% MEM_SIZE], op_tab[((t_process*)(ptr))->opcode - 1].direct_size);
	widht = widht + ((op_tab[((t_process*)(ptr))->opcode - 1].encod == 0) \
		? 1 : 2);
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", widht, ((t_process*)(ptr))->i, \
			(((t_process*)(ptr))->i + widht) % MEM_SIZE);
	i = -1;
	while (++i < widht)
	{
		tmp = ft_itoa_base2((int)cw->arena[((t_process*)(ptr))->i\
						+ i] & 255, "0123456789abcdef");
		if (((int)cw->arena[((t_process*)(ptr))->i + i] & 255) < 16)
			ft_printf("0%s", tmp);
		else
			ft_printf("%s", tmp);
		ft_memdel((void**)&tmp);
		ft_printf(" ");
	}
	ft_printf("\n");
	return (flag);
}
