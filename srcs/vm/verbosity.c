/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbosity.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:46:05 by armajchr          #+#    #+#             */
/*   Updated: 2020/08/05 11:46:46 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int    init_verbotab(t_cw *cw, void *ptr, int flag)
{
    int (*verbotab[6])(t_cw *cw, void *ptr, int flag);

    verbotab[0] = &vprint_essentials;
    verbotab[1] = &vprint_lives;
    verbotab[2] = &vprint_cycle;
    verbotab[3] = &vprint_op;
    verbotab[4] = &vprint_deaths;
    verbotab[5] = &vprint_pcmv;
    return (verbotab[(int)cw->options.v_lvl](cw, ptr, flag));
}

int     vprint_essentials(t_cw *cw, void *ptr,int flag)
{
    if (cw || ptr)
        return (flag);
    return (flag);
}

int     vprint_lives(t_cw *cw, void *ptr, int flag)
{
    if (cw)
        if (flag == 1)
            ft_printf("Player %d (%s) is said to be alive\n", ((t_process*)(ptr))->champ->id, ((t_process*)(ptr))->champ->name);
    return (flag);
}

int     vprint_cycle(t_cw *cw, void *ptr, int flag)
{
    if (ptr)
    {
    if (flag == 1)
    {
        if (cw->tot_lives >= NBR_LIVE || cw->i_check >= MAX_CHECKS)
            ft_printf("Cycle to die is now %d\n", cw->cycle_to_die);
        ft_printf("It is now cycle %d\n", cw->i_cycle);
    }
    }
    return (flag);
}

int     vprint_op(t_cw *cw, void *ptr, int flag)
{
    if (cw)
    {
    if (flag == 1)
    {
        ft_printf("P    %d | %d OK\n", ((t_process*)(ptr))->id, ((t_process*)(ptr))->opcode);
        return (flag);
    }
    else
        ft_printf("P    %d | %d FAIL\n", ((t_process*)(ptr))->id, ((t_process*)(ptr))->opcode);
    }
    return (flag);
}

int     vprint_deaths(t_cw *cw, void *ptr, int flag)
{
    if (flag)
        ft_printf("Process %d hasn't lived for %d cycles (CTD %d)", ((t_process*)(ptr))->id, cw->i_cycle, cw->cycle_to_die);
    return (flag);
}

int     vprint_pcmv(t_cw *cw, void *ptr, int flag)
{
    extern t_op op_tab[17];
    int     widht;

    widht = instruction_width(cw->arena[((t_process*)(ptr))->opcode + 1 % MEM_SIZE], op_tab[((t_process*)(ptr))->opcode].direct_size);
    if (flag)
    {
        ft_printf("ADV %d ", widht + ((op_tab[((t_process*)(ptr))->opcode].encod == 0) ? 1 : 2));
    }
    return (flag);
}
