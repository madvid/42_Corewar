/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:29:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/13 01:17:49 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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

static int		is_dump_option(char *arg, t_parse *p)
{
	p->options->dump = (ft_strequ(arg, "-dump") == 1) ? 1 : 0;
	return (p->options->dump);
}

/*
** Function:
** Description:
**	Function checks if the str arg is the flag option to attribute a specific
**	number to the following chafmpion.
** Return:
**	1: if arg is the attribution number flag
**	0: otherwise
*/

static int		is_n_flag(char *arg)
{
	return (ft_strequ(arg, "-n"));
}

/*
**
**
**
*/

static int		is_valid_nb_champ(char *nb)
{
	if (!ft_str_isnumber(nb))
	{
		ft_putendl("Error, champion number MUST BE a number.");
		return (0);
	}
	if (ft_strlen(nb) > 2)
	{
		ft_putendl("Error, champion number must be 1, 2, 3 or 4.");
		return (0);
	}
	if (!(nb[0] >= '1' && nb[0] <= '4'))
	{
		ft_putendl("Error, champion number must be 1, 2, 3 or 4.");
		return (0);
	}
	return (1);
}

/*
** Function: ft_init_parse_value
** Description:
**
** Return:
**
*/

static void		vm_init_parse_value(t_parse *p)
{
	p->nb_champ = 0;
	p->id_champ = 0;
	p->options->dump = 0;
	p->options->nbr_cycle = 0;
	p->options->n = 0;
}

/*
** Function: is_valid_parameter
** Description:
**	
**
** Return:
**	1: parameters is valid
**	0: parameters is not valid
*/

static int		is_valid_parameter(char *str)
{
	if (ft_strequ(str, "-n") == 1)
		return (1);
	else if (is_valid_nb_champ(str))
		return (1);
	else if (is_valid_champ_filename(str))
		return (1);
	else
		return (0);
}

/*
** Function: vm_parsing
** Description:
**	Parsing of the standard inputs of the executable corewar (the VM)
**	the informations are stored in the structure p of type t_parse.
**	Notice that we just verified the validity of the arguments on the stdin
** and not the validity of the bytecode files (which is performed later).
*/

/*
** Remarque:
**	Il faudra tester le retour de ft_atoull, je suspecte que lorsque la str
**	n'est pas correct, ne pas être en mesure de relever qu'il y a une erreur
*/

int				vm_parsing(char **av, t_parse *p, t_list **lst_champs)
{
	static int		i;

	i = 1;
	printf("valeur de i:%d\n", i);
	if (av[i] && is_dump_option(av[i], p) == 1)
		p->options->dump = 1;
	printf("valeur de i:%d\n", i);
	if (av[++i] && p->options->dump == 1 && ft_is_positive_int(av[i]))
		p->options->nbr_cycle = ft_atoi(av[i++]);
	printf("valeur de i:%d\n", i);
	while (av[i] && p->nb_champ < 4 && !is_valid_parameter(av[i]))
	{
		if (is_n_flag(av[i++]))
			p->options->n = 1;
		if (av[i] && p->options->n && is_valid_nb_champ(av[i]))
				p->id_champ = ft_atoi(av[i++]);
		if (av[i])
		{
			if (!is_valid_champ_filename(av[i]))
				return (vm_error_manager((int)CD_BD_CHAMP_NB, p->error));
			if (!vm_create_champion(lst_champs, av[i], p))
				return (vm_error_manager((int)CD_MEM_CHAMP, p->error));
			i++;
		}
	}
	printf("valeur de i:%d END\n", i);
	return (1);
}

/*
** Function: vm_init_parse
** Description:
**
** Return:
**
*/

int				vm_init_parse(t_parse **p)
{
	int		i;
	static	char	*msg[]={M_USAGE, M_DUMP, M_BD_VAL, M_BD_CHAMP_NB, M_MEM_CHAMP, NULL};

	i = 0;
	if (!(*p = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (vm_init_parse_error(0, p));
	if (!((*p)->error = (char**)ft_memalloc(sizeof(char*) * (int)NB_ERROR_MSG)))
		return (vm_init_parse_error(1, p));
	while (i < (int)NB_ERROR_MSG)
	{
		if (!((*p)->error[i] = ft_strdup(msg[i])))
		{
			while (--i >= 0)
				ft_strdel(&((*p)->error[i]));
			free((*p)->error);
			(*p)->error = NULL;
			return (vm_init_parse_error(2, p));
		}
		i++;
	}
	if (!((*p)->options = (t_options*)ft_memalloc(sizeof(t_options))))
		return (vm_init_parse_error(3, p));
	vm_init_parse_value(*p);
	return (1);
}
