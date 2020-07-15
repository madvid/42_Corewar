/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:42:17 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 15:46:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int ac, char **av)
{
	t_parse		*p;
	t_list		*lst_champs;

	p = NULL;
	lst_champs = NULL;
	if (ac > 1)
	{
		if (!vm_init_parse(&p) || !vm_parsing(av, p, &lst_champs))
			return (0);
		if (vm_champ_parse(&lst_champs, p->error) == 0)
			return (0);
	}
	else
		return (vm_error_manager((int)CD_USAGE, p->error));
	// vm_print_parsing(p);
	vm_print_champ_list(lst_champs);
	return (0);
}
