/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:46:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/19 10:18:17 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		init_verbotab(t_cw *cw, void *ptr, int flag)
{
	int (*verbotab[6])(t_cw *cw, void *ptr, int flag);

	verbotab[0] = &vprint_essentials;
	verbotab[1] = &vprint_lives;
	verbotab[2] = &vprint_cycle;
	verbotab[3] = &vprint_op;
	verbotab[4] = &vprint_deaths;
	verbotab[5] = &vprint_pcmv;
	(cw->options->v_lvl & 0b00000100) ? verbotab[3](cw, ptr, flag) : flag;
	(cw->options->v_lvl & 0b00000001) && ((t_process*)ptr)->opcode == 1 ?
		verbotab[1](cw, ptr, flag) : flag;
	(cw->options->v_lvl & 0b00000010) ? verbotab[2](cw, ptr, flag) : flag;
	(cw->options->v_lvl & 0b00010000) ? verbotab[5](cw, ptr, flag) : flag;
	return (flag);
}

int		vprint_essentials(t_cw *cw, void *ptr, int flag)
{
	if (cw || ptr)
		return (flag);
	return (flag);
}

void	free_tmp_v_tools(char *tmp, char **arg)
{
	int		i;

	if (tmp)
		ft_memdel((void**)&tmp);
	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			if (arg[i])
				ft_memdel((void**)&arg[i]);
			i++;
		}
		ft_memdel((void**)&arg);
	}
}