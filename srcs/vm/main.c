/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/07 14:42:19 by armajchr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			main(int ac, char **av)
{
	t_parse		*p;
	t_cw		*cw;

	p = NULL;
	cw = NULL;
	if (ac > 1)
	{
		if (!vm_init_parse(&p) || !vm_parsing(av, &p))
			return (0);
		if (vm_champ_parse(&(p->lst_champs), &p) == 0)
			return (0);
	}
	else
		return (vm_error_manager((int)CD_USAGE, NULL, NULL));
	// tool_print_parsing(p);
	// tool_print_champ_list(p->lst_champs);
	vm_cw_arena_init(&cw, &p);
	vm_champion_introduction(p->lst_champs);
	// vm_execution(cw, p);
	if (p->options->sdl == true)
		visualizer(cw);
	else
		vm_execution(cw, p);
	vm_error_manager(FIN_DU_GAME, &p, &cw);
	// tool_print_all_processors(cw->process);
	// vm_cw_arena_init(&cw, &p);
	// tool_print_arena(cw->arena, (size_t)MEM_SIZE, p);
	return (0);
}
