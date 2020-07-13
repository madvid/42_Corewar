/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:00:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/13 16:13:46 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vm.h"

void	vm_print_parsing(t_parse *p)
{
	printf("variable t_parse p:\n");
	printf("   p->nb_champ = %d\n", p->nb_champ);
	printf("   p->options->dump = %d\n", p->options->dump);
	printf("   p->options->nbr_cycle = %ld\n", p->options->nbr_cycle);
	printf("   p->options->n = %d\n", p->options->n);
}

void	vm_print_champ_list(t_list *lst_champs)
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
		printf("  next:|%p|\n", xplr->next);
		//printf("   champ_file : %s\n", ((t_champ*)(xplr->cnt)->bytecode));
		i++;
		xplr = xplr->next;
	}
}