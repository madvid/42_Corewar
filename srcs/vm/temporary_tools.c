/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:00:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 12:22:08 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_print_parsing(t_parse *p)
{
	printf("variable t_parse p:\n");
	printf("   p->nb_champ = %d\n", p->nb_champ);
	printf("   p->options->dump = %d\n", p->options->dump);
	printf("   p->options->nbr_cycle = %ld\n", p->options->nbr_cycle);
	printf("   p->options->n = %d\n", p->options->n);
}

static void	print_chp_bcode(char *bcode, int l_bcode)
{
	int		i;
	int		width_line = 32;

	i = 0;

	printf("   bytecode:");
	while (i < l_bcode)
	{
		if (i % width_line == 0)
			printf("|\n       |");
		if (((int)bcode[i] & 255) < 16)
			printf("0");
		printf("%x ", ((int)bcode[i] & 255));
		i++;
	}
	printf("|\n");
}

void		vm_print_champ_list(t_list *lst_champs)
{
	t_list	  *xplr;
	int		 i = 1;

	xplr = lst_champs;
	while (xplr)
	{
		printf("Champion #%d:\n", i);
		printf("   id : |%d|\n", ((t_champ*)(xplr->cnt))->id);
		printf("   champ_file : |%s|\n", ((t_champ*)(xplr->cnt))->champ_file);
		printf("   name : |%s|\n", ((t_champ*)(xplr->cnt))->name);
		printf("   comment : |%s|\n", ((t_champ*)(xplr->cnt))->comment);
		printf("   l_bytecode : |%d|\n", ((t_champ*)(xplr->cnt))->l_bytecode);
		print_chp_bcode(((t_champ*)(xplr->cnt))->bytecode, ((t_champ*)(xplr->cnt))->l_bytecode);
		printf("  next:|%p|\n", xplr->next);
		//printf("   champ_file : %s\n", ((t_champ*)(xplr->cnt)->bytecode));
		i++;
		xplr = xplr->next;
	}
}