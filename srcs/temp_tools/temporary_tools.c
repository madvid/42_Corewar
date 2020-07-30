/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 01:00:59 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/30 10:10:46 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

typedef struct		s_color_champ
{
	size_t		start;
	size_t		end;
	char	*color;
}					t_color_champ;

void		tool_print_parsing(t_parse *p)
{
	printf("variable t_parse p:\n");
	printf("   p->nb_champ = %d\n", p->nb_champ);
	printf("   p->options->dump = %d\n", p->options->dump);
	printf("   p->options->nbr_cycle = %ld\n", p->options->nbr_cycle);
	printf("   p->options->n = %d\n", p->options->n);
}

/*
** Imprime le bytecode des champions (mais possiblement aussi de la zone mémoire)
*/

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
	printf("   \033[1;32mmem position :\033[0m |%d|\n", champ->mem_pos);
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
		printf("   mem position : |%d|\n", ((t_champ*)(xplr->cnt))->mem_pos);
		printf("   l_bytecode : |%d|\n", ((t_champ*)(xplr->cnt))->l_bytecode);
		print_chp_bcode(((t_champ*)(xplr->cnt))->bytecode, ((t_champ*)(xplr->cnt))->l_bytecode);
		printf("  next:|%p|\n", xplr->next);
		//printf("   champ_file : %s\n", ((t_champ*)(xplr->cnt)->bytecode));
		i++;
		xplr = xplr->next;
	}
}

/*
** Fonction pour imprimer la zone memoire correspondant à l'id-arène.
** Parametres: l'arene au sein de la struct cw et la taille (MEM_SIZE)
*/

void		tool_print_id_arena(int *id_arena, size_t mem_size, t_parse *p)
{
	size_t			i;
	int				width_line;
	t_color_champ	**champ;
	static char		*color[] = {"\033[0m", "\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m"};
	int				j = 0;
	t_list			*l_champ;

	i = 0;
	width_line = 32;
	l_champ = p->lst_champs;
	champ = (t_color_champ**)ft_memalloc(sizeof(t_color_champ*) * p->nb_champ);
	while (j < p->nb_champ)
	{
		champ[j] = (t_color_champ*)ft_memalloc(sizeof(t_color_champ));
		champ[j]->start = ((t_champ*)(l_champ->cnt))->mem_pos;
		champ[j]->end = champ[j]->start + ((t_champ*)(l_champ->cnt))->l_bytecode;
		champ[j]->color = color[j + 1];
		j++;
		l_champ = l_champ->next;
	}
	printf("\033[1;36m|>---------------------------------------- [ID ARENA] ----------------------------------------<|\033[0m ");
	while (i < mem_size)
	{
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->start)
				printf("%s", champ[j]->color);
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->end)
				printf("%s", color[0]);
		if (i % width_line == 0)
			printf("\n");
		printf("%d  ", id_arena[i]);
		i++;
	}
	printf("\n\033[1;36m|>------------------------------------------- [FIN] ------------------------------------------<|\033[0m\n");
}

/*
** Fonction pour imprimer la zone memoire correspondant à l'arène.
** Parametres: l'arene au sein de la struct cw et la taille (MEM_SIZE)
*/

void		tool_print_arena(char *arena, size_t mem_size, t_parse *p)
{
	size_t			i;
	int				width_line;
	t_color_champ	**champ;
	static char		*color[] = {"\033[0m", "\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m"};
	int				j = 0;
	t_list			*l_champ;

	i = 0;
	width_line = 64;
	l_champ = p->lst_champs;
	champ = (t_color_champ**)ft_memalloc(sizeof(t_color_champ*) * p->nb_champ);
	while (j < p->nb_champ)
	{
		champ[j] = (t_color_champ*)ft_memalloc(sizeof(t_color_champ));
		champ[j]->start = ((t_champ*)(l_champ->cnt))->mem_pos;
		champ[j]->end = champ[j]->start + ((t_champ*)(l_champ->cnt))->l_bytecode;
		// printf("champ[j=%d]->start = %lu\n", j, champ[j]->start);
		// printf("champ[j=%d]->end = %lu\n", j, champ[j]->end);
		champ[j]->color = color[j + 1];
		j++;
		l_champ = l_champ->next;
	}
	printf("\033[1;31m|>------------------------------------------ [ARENA] -----------------------------------------<|\033[0m ");
	while (i < mem_size)
	{
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->start)
				printf("%s", champ[j]->color);
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->end)
				printf("%s", color[0]);
		if (i % width_line == 0)
			printf("\n");
		if (((int)arena[i] & 255) < 16)
			printf("0");
		printf("%x ", ((int)arena[i] & 255));
		i++;
	}
	printf("\n\033[1;31m|>------------------------------------------- [FIN] ------------------------------------------<|\033[0m\n");
}

/*static int	p_atoint(char *reg)
{
	int		ret;

	ret = 0;
	ret = (((int)reg[0] & 255) << 24) + (((int)reg[1] & 255) << 16) + (((int)reg[2] & 255) << 8) + (((int)reg[3] & 255));
	return (ret);
}*/


/*
** Imprime le contenue du processeur donné en paramètre.
*/

void		tool_print_processor(t_process *process, int nb)
{
	printf(" ______________________________________________________________\n");
	printf("|_ _ _ _ _ _ _ _ _ _ _ _ _ _PROCESS #%d_ _ _ _ _ _ _ _ _ _ _ _ _|\n", nb);
	printf("| id:__________%d                                               |\n", process->id);
	printf("| carry:_______%d                                               |\n", process->carry);
	printf("| opcode:______%X                                               |\n", process->opcode);
	printf("| n_lives:_____%2d                                              |\n", process->n_lives);
	printf("| last_live:___%2d                                              |\n", process->last_live);
	printf("| wait_cycles:_%3d                                             |\n", process->wait_cycles);
	printf("| jump:________%d                                               |\n", process->jump);
	printf("| position:____%14p                                  |\n", process->position);
	printf("| pc:__________%14p                                  |\n", process->pc);
	printf("|                ___r1___   ___r2___   ___r3___   ___r4___     |\n");
	printf("| registers:___| %2d | %2d | %2d | %2d |   |\n", process->registers[0], process->registers[1], process->registers[2], process->registers[3]);
	printf("|            r5| %2d | %2d | %2d | %2d |r8 |\n", process->registers[4], process->registers[5], process->registers[6], process->registers[7]);
	printf("|            r7| %2d | %2d | %2d | %2d |r12|\n", process->registers[8], process->registers[9], process->registers[10], process->registers[11]);
	printf("|              | %2d | %2d | %2d | %2d |r16|\n", process->registers[12], process->registers[13], process->registers[14], process->registers[15]);
	printf("| adrchamp:____%14p                                  |\n", process->champ);
	printf("|______________________________________________________________|\n");
}


/*
** Imprime le contenue de tous les processeurs (liste donnée en paramètre).
*/

void		tool_print_all_processors(t_list *processes)
{
	t_list	*xplr;
	int		nb;

	nb = 0;
	xplr = processes;
	while(xplr && xplr->cnt && (t_process*)(xplr->cnt))
	{
		// printf("valeur xplr->cnt:%p\n", (t_process*)(xplr->cnt));
		tool_print_processor((t_process*)(xplr->cnt), nb);
		// printf("valeur xplr->next:%p\n", xplr->next);
		xplr = xplr->next;
		nb++;
	}
	printf("- - - - END OF ALL PROCESSES\n\n");
}
