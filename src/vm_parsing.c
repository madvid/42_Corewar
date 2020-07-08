/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 13:29:46 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/08 15:35:51 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
	p->option->dump = (ft_streq(arg, "-dump") == 1) ? 1 : 0;
	return (p->option->dump);
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

static int		is_nbchamp_option(char *arg)
{
	return (ft_strequ(arg, "-n"));
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

	tmp = 1;
	while (++i < ac)
	{
		if (is_dump_option(av[i]) == 1 && av[++i] != NULL)
		{
			p->option->nbr_cycle = ft_atoull(av[i]);
			i++;
		}
		if (is_nbchamp_option(av[i]) == 1)
		{
			if (av[++i] && is_within_int(av[i]))
			{
				tmp = ft_atoi(av[i]);
				
				i++;
			}
		}



}