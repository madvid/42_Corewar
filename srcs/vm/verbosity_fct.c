/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:15:39 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/11 17:04:41 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		vprint_lives(t_cw *cw, void *ptr, int flag)
{
	if (cw)
		if (flag == 1)
			ft_printf("Player %d (%s) is said to be alive\n", \
					((t_process*)(ptr))->champ->id, \
					((t_process*)(ptr))->champ->name);
	return (flag);
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

	if (cw)
	{
		if (flag == 1)
		{
			ft_printf("P\t%d | %s %sOK\n", ((t_process*)(ptr))->id, \
					op_tab[((t_process*)(ptr))->opcode - 1].name, \
					args_to_str(cw, ((t_process*)(ptr))));
			return (flag);
		}
		else
			ft_printf("P\t%d | %s %sFAIL\n", ((t_process*)(ptr))->id, \
					op_tab[((t_process*)(ptr))->opcode - 1].name, \
					args_to_str(cw, ((t_process*)(ptr))));
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
	extern t_op	op_tab[17];
	int			widht;
	int			i;

	widht = instruction_width(cw->arena[((t_process*)(ptr))->opcode + 1 \
			% MEM_SIZE], op_tab[((t_process*)(ptr))->opcode - 1].direct_size);
	widht = widht + ((op_tab[((t_process*)(ptr))->opcode - 1].encod == 0) \
		? 1 : 2);
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", widht, ((t_process*)(ptr))->i, \
			(((t_process*)(ptr))->i + widht) % MEM_SIZE);
	i = -1;
	while (++i < widht)
	{
		if (((int)cw->arena[((t_process*)(ptr))->i + i] & 255) < 16)
			ft_printf("0%s", ft_itoa_base2((int)cw->arena\
			[((t_process*)(ptr))->i + i] & 255, "0123456789abcdef"));
		else
			ft_printf("%s", ft_itoa_base2((int)cw->arena[((t_process*)(ptr))->i\
						+ i] & 255, "0123456789abcdef"));
		ft_printf(" ");
	}
	ft_printf("\n");
	return (flag);
}
