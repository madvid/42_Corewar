/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntbf_verbosity_fct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:15:39 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/26 09:45:44 by mdavid           ###   ########.fr       */
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
			ft_printf("Player %d (%s) is said to be alive\n" \
				, ((t_champ*)(xplr->cnt))->id \
				, ((t_champ*)(xplr->cnt))->name);
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

void	free_args(char **arg, char *a, char *b)
{
	int		i;

	i = -1;
	while (arg[++i])
		ft_memdel((void*)&arg[i]);
	ft_memdel((void*)&arg);
	if (a)
		ft_memdel((void*)&a);
	if (b)
		ft_memdel((void*)&b);
}

int		vprint_op(t_cw *cw, void *ptr, int flag)
{
	extern t_op op_tab[17];
	char		*a;
	char		*b;
	char		*tmp;
	char		**arg;

	tmp = (flag == 1) ? "OK" : "FAILED";
	arg = ft_strsplit(args_to_str(cw, (t_process*)(ptr)), 32);
	if (!arg)
		return (0);
	a = NULL;
	b = NULL;
	if (((t_process*)(ptr))->opcode == 12 || ((t_process*)(ptr))->opcode == 15)
		opcode_v12(cw, ptr, a, arg);
	else
		opcode_g(cw, ptr, tmp);
	if (((t_process*)(ptr))->opcode == 11)
		opcode_v11(ptr, a, b, arg);
	if (((t_process*)(ptr))->opcode == 10)
		opcode_v10(ptr, a, b, arg);
	free_args(arg, a, b);
	return (flag);
}

int		vprint_deaths(t_cw *cw, void *ptr, int flag)
{
	if (flag)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
			((t_process*)(ptr))->id, cw->i_cycle - \
			((t_process*)(ptr))->last_live, cw->cycle_to_die);
	return (flag);
}

int		vprint_pcmv(t_cw *cw, void *ptr, int flag)
{
	extern t_op	op_tab[17];
	int			widht;
	t_process	*p;

	p = (t_process*)ptr;
	if (cw->options->v_p == 0)
	{
		if (op_tab[p->opcode - 1].encod == 1)
			widht = instruction_width(cw->arena[(p->i + 1) \
				% MEM_SIZE], op_tab[p->opcode - 1]);
		else
			widht = op_tab[p->opcode - 1].direct_size == 1 ? 2 : 4;
		widht += ((op_tab[p->opcode - 1].encod == 0) ? 1 : 2);
		if (p->opcode == 9 && flag == 1)
			return (flag);
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", \
			(p->opcode == 3 || p->opcode == 11) ? flag : widht, p->i, \
			p->i + ((p->opcode == 3 || p->opcode == 11) ? flag : widht) \
			% MEM_SIZE);
		pcmv_print(cw, ptr, flag, widht);
	}
	return (flag);
}
