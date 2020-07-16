/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:00:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/16 15:04:45 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		tool_print_parsing(t_parse *p)
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
	int		width_line;

	i = 0;
	width_line = 32;
	printf("   \033[1;32mbytecode:\033[0m");
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

/*
** Fonction qui affiche 1 champion, celui reçu en parametre.
*/

void		tool_print_champ(t_champ *champ)
{
	printf("\033[0;33mChampion:\033[0m\n");
	printf("   \033[1;32mchamp_file :\033[0m |%s|\n", champ->champ_file);
	printf("   \033[1;32mname :\033[0m |%s|\n", champ->name);
	printf("   \033[1;32mcomment :\033[0m |%s|\n", champ->comment);
	printf("   \033[1;32mid :\033[0m |%d|\n", champ->id);
	printf("   \033[1;32mmem position :\033[0m |%p|\n", champ->mem_pos);
	printf("   \033[1;32ml_bytecode :\033[0m |%d|\n", champ->l_bytecode);
	print_chp_bcode(champ->bytecode, champ->l_bytecode);
	//printf("   champ_file : %s\n", ((t_champ*)(xplr->cnt)->bytecode));
}

/*
** Fonction qui affiche tous les champions de la liste de champions présent dans la structure p (parsing)
*/

void		tool_print_champ_list(t_list *lst_champs)
{
	t_list		*xplr;
	int			i;

	i = 1;
	xplr = lst_champs;
	while (xplr)
	{
		printf("\033[0;33mChampion #%d:\033[0m\n", i);
		printf("   id : |%d|\n", ((t_champ*)(xplr->cnt))->id);
		printf("   champ_file : |%s|\n", ((t_champ*)(xplr->cnt))->champ_file);
		printf("   name : |%s|\n", ((t_champ*)(xplr->cnt))->name);
		printf("   comment : |%s|\n", ((t_champ*)(xplr->cnt))->comment);
		printf("   mem position : |%p|\n", ((t_champ*)(xplr->cnt))->mem_pos);
		printf("   l_bytecode : |%d|\n", ((t_champ*)(xplr->cnt))->l_bytecode);
		print_chp_bcode(((t_champ*)(xplr->cnt))->bytecode, ((t_champ*)(xplr->cnt))->l_bytecode);
		printf("  next:|%p|\n", xplr->next);
		//printf("   champ_file : %s\n", ((t_champ*)(xplr->cnt)->bytecode));
		i++;
		xplr = xplr->next;
	}
}

/*
** Fonction pour imprimer la zone memoire correspondant à l'arène.
*/

void		tool_print_arena(char *arena, size_t mem_size)
{
	size_t	i;
	int		width_line;

	i = 0;
	width_line = 32;
	printf("\033[1;31m|>------------------------------------------ [ARENA] -----------------------------------------<|\033[0m");
	while (i < mem_size)
	{
		if (i % width_line == 0)
			printf("\n");
		if (((int)arena[i] & 255) < 16)
			printf("0");
		printf("%x ", ((int)arena[i] & 255));
		i++;
	}
	printf("\n\033[1;31m|>------------------------------------------- [FIN] ------------------------------------------<|\033[0m\n");
}
