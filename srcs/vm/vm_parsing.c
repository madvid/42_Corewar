/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:29:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/08/05 14:58:07 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

/*
** Function: unique_opt
** Description:
**	Verifies if the option flag does not appears already previously.
** Return:
**	1: if the option flag is unique
**	0: if we already encounter the option flag
*/
static int		unique_opt(t_parse *p, char *str)
{
	int		stat;

	stat = 2;
	if (ft_strequ(str, "-dump") == 1)
		return (stat = (p->options->dump == true) ? 0 : 1);
	if (ft_strequ(str, "-a") == 1)
		return (stat = (p->options->aff == true) ? 0 : 1);
	if (ft_strequ(str, "-v") == 1)
		return (stat = (p->options->verbose == true) ? 0 : 1);
	if (ft_strequ(str, "-SDL") == 1)
		return (stat = (p->options->sdl == true) ? 0 : 1);
	return (stat);
}

/*
** Function:
** Description:
**	Checks the precense of option flags and their arguments. It stocks the
**	presence of options and option arguments in p->options.
**	The first argument option invalid brings a return of the associated CODE
**	ERROR.
** Return:
**		0: if all present option flags and arguments are valid.
**		CODE ERROR: if the option argument is invalid.
*/

int				vm_options_flag(char **av, t_parse **p, int *i)
{
	while (av[*i] && (ft_strequ(av[*i], "-dump") || ft_strequ(av[*i], "-v")
		|| ft_strequ(av[*i], "-a") || ft_strequ(av[*i], "-SDL")))
	{
		if (av[*i] && ft_strequ(av[*i], "-a") == 1)
		{
			(*i)++;
			(*p)->options->aff = true;
		}
		if (is_dump_option(av[*i], *p) == 1)
		{
			if (av[++(*i)] && ft_is_positive_int(av[*i]) != -1)
				(*p)->options->dump_cycle = ft_atoi(av[(*i)++]);
			else
				return ((int)CD_DUMP);
		}
		if (av[*i] && ((*p)->options->verbose = ft_strequ(av[*i], "-v")) == 1)
		{
			if (av[++(*i)] && in_verbose_range(av[*i]))
				(*p)->options->v_lvl = (u_int8_t)ft_atoi(av[(*i)++]);
			else
				return ((int)CD_VERB);
		}
		if (av[*i] && ft_strequ(av[*i], "-SDL") == 1)
		{
			(*i)++;
			(*p)->options->sdl = true;
		}
		if (unique_opt(*p, av[*i]) == 0)
			return ((int)CD_UNIQ);
	}
	return (0);
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

static int		is_valid_nb_champ(char *nb)
{
	if (ft_strlen(nb) > 1)
	{
		ft_putendl("Error: champion number must be 1, 2, 3 or 4.");
		return (0);
	}
	if (!(nb[0] >= '1' && nb[0] <= '4'))
	{
		ft_putendl("Error: champion number must be 1, 2, 3 or 4.");
		return (0);
	}
	return (1);
}

/*
** Function: vm_parsing
** Description:
**	Parsing of the standard inputs of the executable corewar (the VM)
**	the informations are stored in the structure p of type t_parse.
**	Notice that we just verified the validity of the arguments on the stdin
** and not the validity of the bytecode files (which is performed later).
*/

int				vm_parsing(char **av, t_parse **p)
{
	int		i;
	int		code_error;

	i = 1;
	if ((code_error = vm_options_flag(av, p, &i)) != 0)
		return(vm_error_manager(code_error, p, NULL));
	while (av[i] && (*p)->nb_champ < 5)
	{
		if (ft_strequ(av[i], "-n") == 1)
		{
			if (av[++i] && is_valid_nb_champ(av[i]))
			{
				(*p)->options->n = 1;
				(*p)->id_champ = (int)(*av[i++] - '0');
			}
			else
				return (vm_error_manager((int)CD_BD_VAL, p, NULL));
		}
		if (av[i] && !is_valid_champ_filename(av[i]))
			return (vm_error_manager((int)CD_BD_CHAMP_NB, p, NULL));
		if (av[i] && !vm_create_champion(&((*p)->lst_champs), av[i++], *p))
			return (vm_error_manager((int)CD_MEM_CHAMP, p, NULL));
	}
	if ((*p)->nb_champ == 0)
		return (vm_error_manager((int)CD_EMPTY_CHP, p, NULL));
	if ((*p)->nb_champ > (int)MAX_PLAYERS)
		return (vm_error_manager((int)CD_MAX_CHAMP, p, NULL));
	return (1);
}
