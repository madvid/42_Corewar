/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 09:59:00 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/03 12:18:27 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vm.h"

static void		tprint_a2(char *a, t_color_champ **champ, char **c, t_parse *p)
{
	size_t		i;
	int			j;

	i = 0;
	while (i < MEM_SIZE)
	{
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->start)
				ft_printf("%s", champ[j]->color);
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->end)
				printf("%s", c[0]);
		if (i % 32 == 0)
			printf("\n");
		if (((int)a[i] & 255) < 16)
			printf("0");
		printf("%x ", ((int)a[i] & 255));
		i++;
	}
	printf("\n\033[1;31m|>%43s [FIN] %42s<|\033[0m\n", " ", " ");
}

/*
** Fonction pour imprimer la zone memoire correspondant à l'arène.
** Parametres: l'arene au sein de la struct cw et la taille (MEM_SIZE)
*/

void			tool_print_arena(char *arena, t_parse *p)
{
	t_color_champ	**champ;
	static char		*color[] = {"\033[0m", "\033[1;31m", "\033[1;32m", \
		"\033[1;33m", "\033[1;34m"};
	int				j;
	t_list			*l_champ;

	j = 0;
	l_champ = p->lst_champs;
	champ = (t_color_champ**)ft_memalloc(sizeof(t_color_champ*) * p->nb_champ);
	while (j < p->nb_champ)
	{
		champ[j] = (t_color_champ*)ft_memalloc(sizeof(t_color_champ));
		champ[j]->start = ((t_champ*)(l_champ->cnt))->mem_pos;
		champ[j]->end = champ[j]->start + \
			((t_champ*)(l_champ->cnt))->l_bytecode;
		champ[j]->color = color[j + 1];
		j++;
		l_champ = l_champ->next;
	}
	printf("\033[1;31m|>%42s [ARENA] %41s<|\033[0m ", " ", " ");
	tprint_a2(arena, champ, color, p);
}

static void		tool_print_proc2(t_process *p)
{
	ft_printf("| registers:___| %8d | %8d | %8d | %8d |   |\n", \
			p->registers[0], p->registers[1], \
			p->registers[2], p->registers[3]);
	ft_printf("|            r5| %8d | %8d | %8d | %8d |r8 |\n", \
			p->registers[4], p->registers[5], \
			p->registers[6], p->registers[7]);
	ft_printf("|            r7| %8d | %8d | %8d | %8d |r12|\n", \
			p->registers[8], p->registers[9], \
			p->registers[10], p->registers[11]);
	ft_printf("|              | %8d | %8d | %8d | %8d |r16|\n", \
			p->registers[12], p->registers[13], \
			p->registers[14], p->registers[15]);
	ft_printf("|____________________________________________________%\
			__________|\n");
}

/*
** Imprime le contenue du processeur donné en paramètre.
*/

void			tool_print_processor(t_process *p, int nb)
{
	ft_printf(" ______________________________________________________%\
			________\n");
	ft_printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _PROCESS #%d_ _ _ _ _ _ _ _ _%\
			_ _ _ _|\n", nb);
	ft_printf("| id:__________%d%47s|\n", p->id, " ");
	ft_printf("| carry:_______%d%47s|\n", p->carry, " ");
	ft_printf("| opcode:______%X%47s|\n", p->opcode, " ");
	ft_printf("| n_lives:_____%2d%46s|\n", p->n_lives, " ");
	ft_printf("| last_live:___%2d%46s|\n", p->last_live, " ");
	ft_printf("| wait_cycles:_%3d%45s|\n", p->wait_cycles, " ");
	ft_printf("| position:____ (0x%.4x)%d%35s|\n", p->i, p->i, " ");
	ft_printf("| pc:__________ (0x%.4x)%d%38s|\n", p->pc, p->pc, " ");
	ft_printf("|%21s___r1___   ___r2___   ___r3___   ___r4___|\n", " ");
	tool_print_proc2(p);
}

/*
** Imprime le contenue de tous les processeurs (liste donnée en paramètre).
*/

void			tool_print_all_processors(t_list *processes)
{
	t_list	*xplr;
	int		nb;

	nb = 0;
	xplr = processes;
	while (xplr && xplr->cnt && (t_process*)(xplr->cnt))
	{
		tool_print_processor((t_process*)(xplr->cnt), nb);
		xplr = xplr->next;
		nb++;
	}
	printf("- - - - END OF ALL PROCESSES\n\n");
}
