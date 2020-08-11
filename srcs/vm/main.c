/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armajchr <armajchr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/11 15:10:00 by armajchr         ###   ########.fr       */
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
	vm_cw_arena_init(&cw, &p);
	vm_champion_introduction(&(p->lst_champs));
	// vm_execution(cw, p);
	ft_printf("<ici 1>\n");
	tool_print_short_champ_list(p->lst_champs);
	if (p->options->sdl == true)
		visualizer(cw, p);
	else
		vm_execution(cw, p);
	vm_error_manager(FIN_DU_GAME, &p, &cw);
	return (0);
}
