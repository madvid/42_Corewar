/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabldel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:48:05 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/13 16:52:43 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Function: ft_strtabldel
** Description:
**	Functions free the memory allocated for the table of strings received in
**	parameters.
*/

void	ft_strtabldel(char ***tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (*tab[i])
	{
		ft_strdel(*tab + i);
		i++;
	}
	free(*tab);
	*tab = NULL;
}