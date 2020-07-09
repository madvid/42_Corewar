/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:52:38 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/09 15:00:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			vm_init_parse_error(int code_error)
{
	ft_putendl("Error from the initialization of the struct parse.");
	return (code_error);
}

int			vm_error_manager(int code_error, char **error)
{
	ft_putendl(error[code_error]);
	return (0);
}