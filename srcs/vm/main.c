/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/02 12:57:42 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <sys/utsname.h>
// #include "visu.h"
#include "vm.h"

/*
**__attribute__((destructor)) void foo(void){while (1); }
*/

int			main(int ac, char **av)
{
	t_parse			*p;
	t_cw			*cw;
	int				code_error;
	// struct utsname	ikernel;

	p = NULL;
	cw = NULL;
	if (ac > 1)
	{
		if (vm_init_parse(&p) != 0 || vm_parsing(av, &p) != 0
			|| vm_champ_parse(&(p->lst_champs), &p) != 0)
			return (0);
	}
	else
		return (vm_error_manager((int)CD_USAGE, NULL, NULL));
	vm_champion_introduction(&(p->lst_champs));
	vm_cw_arena_init(&cw, &p);
	cw->lst_champs = p->lst_champs;
	// uname(&ikernel);
	// if (p->options->sdl == true && ft_strequ(ikernel.sysname, "Darwin") == 1)
	// 	code_error = visualizer(cw, p);
	// else
	// 	code_error = vm_execution(cw);
	code_error = vm_execution(cw);
	vm_error_manager(code_error, &p, &cw);
	return (0);
}
