/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/13 01:26:29 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int ac, char **av)
{
	t_parse		*p;
	t_list		*lst_champs;

	p = NULL;
	lst_champs = NULL;
	if (!vm_init_parse(&p))
		return (0);
	if (ac == 1)
		return (vm_error_manager((int)CD_USAGE, p->error));
	if (ac > 1)
		if (!vm_parsing(av, p, &lst_champs))
			return (0);
	vm_print_parsing(p);
	vm_print_champ_list(lst_champs);
	return (0);
}