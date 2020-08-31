/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/31 20:46:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

int			main(int ac, char **av)
{
	t_parse		*p;
	t_cw		*cw;
	int			code_error;

	p = NULL;
	cw = NULL;
	if (ac > 1)
	{
		if (vm_init_parse(&p) != 0 || vm_parsing(av, &p) != 0)
			return (0);
		if (vm_champ_parse(&(p->lst_champs), &p) == 0)
			return (0);
	}
	else
		return (vm_error_manager((int)CD_USAGE, NULL, NULL));
	vm_champion_introduction(&(p->lst_champs));
	vm_cw_arena_init(&cw, &p);
	cw->lst_champs = p->lst_champs;
	code_error = vm_execution(cw);
	// if (p->options->sdl == true)
	// 	visualizer(cw, p);
	// else
	// 	vm_execution(cw);
	vm_error_manager(code_error, &p, &cw);
	return (0);
}
