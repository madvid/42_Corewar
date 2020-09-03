/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_tools3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 10:00:10 by armajchr          #+#    #+#             */
/*   Updated: 2020/09/03 12:21:32 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vm.h"

void			tool_print_parsing(t_parse *p)
{
	printf("variable t_parse p:\n");
	printf("   p->nb_champ = %d\n", p->nb_champ);
	printf("   p->options->dump = %d\n", p->options->dump);
	printf("   p->options->nbr_cycle = %d\n", p->options->dump_cycle);
	printf("   p->options->n = %d\n", p->options->n);
}

/*
** Affiche l'ensemble des processus (id et position simplement)
*/

void			tool_print_short_processors(t_cw *cw)
{
	t_list		*xplr;
	t_process	*proc;
	int			index;

	xplr = cw->process;
	while (xplr)
	{
		proc = (t_process*)(xplr->cnt);
		index = proc->i;
		ft_printf("P %d -- is at the memory adress : %d (index = %d) -- \
				opcode = %d(w_c = %d)\n", proc->id, proc->i, index, \
				proc->opcode, proc->wait_cycles);
		xplr = xplr->next;
	}
}

/*
** Affiche le contenue de la variable de structure t_arg
*/

void			tool_print_t_arg(t_arg arg)
{
	ft_printf(">> T_ARG <<");
	ft_printf(" - arg.type[0] = %d", arg.type[0]);
	ft_printf(" - arg.type[1] = %d", arg.type[1]);
	ft_printf(" - arg.type[2] = %d", arg.type[2]);
	ft_printf(" - arg.arg[0] = %d", arg.arg[0]);
	ft_printf(" - arg.arg[1] = %d", arg.arg[1]);
	ft_printf(" - arg.arg[2] = %d", arg.arg[2]);
	ft_printf(" - arg.widht = %d\n", arg.widht);
}

static void		tprint_ida(int *id, t_parse *p, char **c, t_color_champ **champ)
{
	size_t	i;
	int		j;

	printf("\033[1;36m|>%39s [ID ARENA] %39s<|\033[0m ", " ", " ");
	i = 0;
	while (i < MEM_SIZE)
	{
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->start)
				printf("%s", champ[j]->color);
		j = -1;
		while (++j < p->nb_champ)
			if (i == champ[j]->end)
				printf("%s", c[0]);
		if (i % 32 == 0)
			printf("\n");
		printf("%d  ", id[i]);
		i++;
	}
	printf("\n\033[1;36m|>%41s [FIN] %42s<|\033[0m\n", " ", " ");
}

/*
** Fonction pour imprimer la zone memoire correspondant à l'id-arène.
** Parametres: l'arene au sein de la struct cw et la taille (MEM_SIZE)
*/

void			tool_print_id_arena(int *id_arena, t_parse *p)
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
	tprint_ida(id_arena, p, color, champ);
}
