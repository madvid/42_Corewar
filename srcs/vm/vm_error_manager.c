/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/11 15:26:01 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

int			vm_init_parse_error(int cd_error, t_parse **p)
{
	int		i;

	i = ((int)NB_ERROR_MSG);
	if (cd_error >= 3)
	{
		while (--i >= 0)
				ft_strdel(&((*p)->error[i]));
	}
	if (cd_error >= 2)
	{
		free((*p)->error);
		(*p)->error = NULL;
	}
	if (cd_error >= 1)
	{
		free(*p);
		*p = NULL;

	}
	ft_putendl("Error from the initialization of the struct parse.");
	return (0);
}

int			vm_error_manager(int code_error, char **error)
{
	ft_putendl(error[code_error]);
	return (0);
}