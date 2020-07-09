/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:29:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/09 17:10:24 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	ft_putendl("is_dump 1");
	p->options->dump = (ft_strequ(arg, "-dump") == 1) ? 1 : 0;
	ft_putendl("is_dump 2");
	return (p->options->dump);
}

/*
** Function:
** Description:
**	Function checks if the str arg is the flag option to attribute a specific
**	number to the following champion.
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

int				vm_parsing(int ac, char **av, t_parse *p)
{
	static int		i;
	int				tmp;
	t_list			*lst_champs;

	tmp = 1;
	i = 1;
	lst_champs = NULL;
	if (!av[i])
		return(vm_error_manager((int)CD_USAGE, p->error));
	ft_putendl("ici 1");
	if (is_dump_option(av[i], p) == 1 && av[++i])
	{
		ft_putendl("ici 2");
		if (ft_is_positive_int(av[i]))
			p->options->nbr_cycle = ft_atoi(av[i++]);
		else
			return(vm_error_manager((int)CD_DUMP, p->error));
	}
	while (av[i] && i < ac)
	{
		if (is_n_flag(av[i]) == 1 && av[++i] && is_valid_nb_champ(av[i]))
			if (!vm_create_champion(&lst_champs, av, i))
				return (vm_error_manager((int)CD_BD_VAL, p->error));
	}
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
	static	char	*msg[]={M_USAGE, M_DUMP, M_BD_VAL, NULL};

	i = 0;
	if (!(*p = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (vm_init_parse_error(0));
	if (!((*p)->error = (char**)ft_memalloc(sizeof(char*) * (int)NB_ERROR_MSG)))
		return (vm_init_parse_error(0));
	while (i < (int)NB_ERROR_MSG)
	{
		if (!((*p)->error[i] = ft_strdup(msg[i])))
		{
			while (i >= 0)
				ft_strdel(&((*p)->error[i]));
			free((*p)->error);
			(*p)->error = NULL;
			return (vm_init_parse_error(0));
		}
		i++;
	}
	if (!((*p)->options = (t_options*)ft_memalloc(sizeof(t_options))))
		return (vm_init_parse_error(0));
	return (1);
}
