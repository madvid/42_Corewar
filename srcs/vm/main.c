/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/24 18:52:25 by mdavid           ###   ########.fr       */
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
	vm_champion_introduction(&(p->lst_champs));
	vm_cw_arena_init(&cw, &p);
	cw->lst_champs = p->lst_champs;
	// vm_execution(cw, p);
	if (p->options->sdl == true)
		visualizer(cw, p);
	else
		vm_execution(cw);
	vm_error_manager(FIN_DU_GAME, &p, &cw);
	//system("leaks vm");
	return (0);
}
