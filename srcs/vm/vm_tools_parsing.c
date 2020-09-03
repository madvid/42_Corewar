/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_tools_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:25:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/03 16:30:32 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Function: is_dump_option
** Description:
**	Function check if the string arg is the option flag -dump. If so, flag for
**	option dump is set to 1 (otherwise 0).
** Return:
**	1: if the str arg is the flag option dump
**	0: if not
*/

int		is_dump_option(char *arg, t_parse *p)
{
	p->options->dump = (ft_strequ(arg, "-dump") == 1) ? 1 : 0;
	return (p->options->dump);
}

/*
** Function: in_verbose_range
** Description:
**	Function checks if the str arg is a positive number or null
**	within 0 and 31 both included.
** Return:
**	1: if arg is in verbose level range
**	0: otherwise
*/

int		in_verbose_range(char *arg)
{
	int		option;

	if (ft_is_positive_int(arg) == -1)
		return (0);
	option = ft_atoi(arg);
	if (!(option >= 0 && option <= 31))
		return (0);
	return (1);
}

/*
** Function: is_valid_nb_champ
** Description:
**	Checks if the number given by the user is a positive int sinfle digit
**	in [1 ; 4].
** Return:
**	1: if the number for the id champion is correct.
**	0: otherwise.
*/

int		is_valid_nb_champ(char *nb)
{
	if (ft_strlen(nb) > 1 || !(nb[0] >= '1' && nb[0] <= '4'))
		return (0);
	return (1);
}

/*
** Function: id_number_chp_flag
** Description:
**	Checks if the argument is the flag to specify the id of the champion.
**	Plus if the flag is the good one, function checks if the specify ID
**	is available.
** Return:
**	1: if av[i] is "-n" and ID is available
**	0: otherwise
*/

int		id_number_chp_flag(t_parse **p, char **av, int *i)
{
	if (ft_strequ(av[*i], "-n") == 1)
	{
		if (av[++(*i)] && is_valid_nb_champ(av[*i]))
		{
			(*p)->options->n = 1;
			(*p)->id_champ = (int)(av[(*i)++][0] - '0');
		}
		else
			return (0);
	}
	return (1);
}
