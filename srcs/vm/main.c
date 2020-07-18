/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/18 22:15:33 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** ZONE POUR TESTER DES BOUTS DE CODE OU COMPORTEMENT
*/

/*
static void	test(t_parse *p)
{
	tool_print_champ_list(p->lst_champs);
	printf("Avant la supression de la liste de champions\n");
	ft_lstdel(&(p->lst_champs), ft_lst_fdel);
	p->lst_champs = NULL;
	printf("Après la supression de la liste de champions\n");
	tool_print_champ_list(p->lst_champs);
}
*/

/*
** FIN DE LA ZONE
*/

int			main(int ac, char **av)
{
	t_parse		*p;
	t_cw		*cw;

	p = NULL;
	cw = NULL;
	if (ac > 1)
	{
		if (!vm_init_parse(&p) || !vm_parsing(av, p))
			return (0);
		if (vm_champ_parse(&(p->lst_champs), p->error) == 0)
			return (0);
	}
	else
		return (vm_error_manager((int)CD_USAGE, p->error));
	// tool_print_parsing(p);
	// tool_print_champ_list(p->lst_champs);
	// test(p);
	vm_cw_arena_init(&cw, p);
	tool_print_arena(cw->arena, (size_t)MEM_SIZE);
	return (0);
}
